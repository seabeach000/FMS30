/*
* Copyright (c) 2011 Sveriges Television AB <info@casparcg.com>
*
* This file is part of CasparCG (www.casparcg.com).
*
* CasparCG is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* CasparCG is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with CasparCG. If not, see <http://www.gnu.org/licenses/>.
*
* Author: Robert Nagy, ronag89@gmail.com
*/

#include "../StdAfx.h"

#include "AsyncEventServer_Serial.h"

#include <algorithm>
#include <array>
#include <string>
#include <set>
#include <memory>
#include <functional>

#include <boost/asio.hpp>
#include <boost/lexical_cast.hpp>

#include <tbb/mutex.h>
#include <tbb/concurrent_hash_map.h>
#include <tbb/concurrent_queue.h>

using namespace boost::asio;

namespace caspar { namespace IO {
	
	template <typename ElemT>
	struct HexTo {
		ElemT value;
		operator ElemT() const { return value; }
		friend std::istream& operator >> (std::istream& in, HexTo& out) {
			in >> std::hex >> out.value;
			return in;
		}
	};
class Rserial;

typedef std::set<spl::shared_ptr<Rserial>> Rserial_set;

class Rserial : public spl::enable_shared_from_this<Rserial>
{   
	typedef tbb::concurrent_hash_map<std::wstring, std::shared_ptr<void>> lifecycle_map_type;
	typedef tbb::concurrent_queue<std::string>	send_queue;
	serial_port											*fd_;
	std::shared_ptr<boost::asio::io_service>		service_;
	const spl::shared_ptr<Rserial_set>				Rserial_set_;
	protocol_strategy_factory<char>::ptr			protocol_factory_;
	std::shared_ptr<protocol_strategy<char>>		protocol_;

	std::array<char, 32768>							data_;
	lifecycle_map_type								lifecycle_bound_objects_;
	send_queue										send_queue_;
	bool											is_writing_;
	unsigned short									port_;

	class Rserial_holder : public client_connection<char>
	{
		std::weak_ptr<Rserial> Rserial_;
	public:
		explicit Rserial_holder(std::weak_ptr<Rserial> conn) : Rserial_(std::move(conn))
		{}

		void send(std::basic_string<char>&& data) override
		{
			std::string senddata;
			for (int i  = 0; i<data.size();i+=2)
			{
				unsigned char  sdt = static_cast<unsigned char>(boost::lexical_cast<HexTo<int>>(data.substr(i, 2)));
				senddata.push_back(sdt);
			}
			data = senddata;
			auto conn = Rserial_.lock();

			if (conn)
				conn->send(std::move(data));
		}
		void disconnect() override
		{
			auto conn = Rserial_.lock();

			if (conn)
				conn->disconnect();
		}
		std::wstring address() const override
		{
			auto conn = Rserial_.lock();

			if (conn)
				return conn->address();
			else
				return L"[destroyed-connection]";
		}
		void add_lifecycle_bound_object(const std::wstring& key, const std::shared_ptr<void>& lifecycle_bound) override
		{
			auto conn = Rserial_.lock();

			if (conn)
				return conn->add_lifecycle_bound_object(key, lifecycle_bound);
		}

		std::shared_ptr<void> remove_lifecycle_bound_object(const std::wstring& key) override
		{
			auto conn = Rserial_.lock();

			if (conn)
				return conn->remove_lifecycle_bound_object(key);
			else
				return std::shared_ptr<void>();
		}
	};

public:
	static spl::shared_ptr<Rserial> create(std::shared_ptr<boost::asio::io_service> service,
		unsigned short port, 
		const protocol_strategy_factory<char>::ptr& protocol, spl::shared_ptr<Rserial_set> Rserialset)
	{
		spl::shared_ptr<Rserial> con(new Rserial(std::move(service), std::move(port), 
			std::move(protocol), std::move(Rserialset)));
		con->init();
		con->read_some();
		return con;
    }

	void init()
	{
		fd_->set_option(serial_port::baud_rate(38400));                         //比特率

		fd_->set_option(serial_port::flow_control(serial_port::flow_control::none)); //流量控制

		fd_->set_option(serial_port::parity(serial_port::parity::odd));            //奇偶校验

		fd_->set_option(serial_port::stop_bits(serial_port::stop_bits::one));        //停止位

		fd_->set_option(serial_port::character_size(8));                       //数据位
		//async_read(*fd_, buffer(buf), boost::bind(&handle_read, this, buf, _1, _2));

		protocol_ = protocol_factory_->create(spl::make_shared<Rserial_holder>(shared_from_this()));
	}

	~Rserial()
	{
		CASPAR_LOG(debug) << print() << L" Rserial destroyed.";
	}

	std::wstring print() const
	{
		return L"async_event_server_serial;";
	}
	std::wstring address() const
	{
		return L"COM" + boost::lexical_cast<std::wstring>(port_);
	}
	std::wstring isopen() const
	{
		return fd_->is_open() ? L"COM"+boost::lexical_cast<std::wstring>(port_) : L"no-open";
		
	}

	void send(std::string&& data)
	{
		send_queue_.push(std::move(data));
		auto self = shared_from_this();
		service_->dispatch([=] { self->do_write(); });
	}

	void disconnect()
	{
		auto self = shared_from_this();
		service_->dispatch([=] { self->stop(); });
	}

	void add_lifecycle_bound_object(const std::wstring& key, const std::shared_ptr<void>& lifecycle_bound)
	{
		//thread-safe tbb_concurrent_hash_map
		lifecycle_bound_objects_.insert(std::pair<std::wstring, std::shared_ptr<void>>(key, lifecycle_bound));
	}
	std::shared_ptr<void> remove_lifecycle_bound_object(const std::wstring& key)
	{
		//thread-safe tbb_concurrent_hash_map
		lifecycle_map_type::const_accessor acc;
		if (lifecycle_bound_objects_.find(acc, key))
		{
			auto result = acc->second;
			lifecycle_bound_objects_.erase(acc);
			return result;
		}
		return std::shared_ptr<void>();
	}

private:
	void do_write()	//always called from the asio-service-thread
	{
		if(!is_writing_)
		{
			std::string data;
			if(send_queue_.try_pop(data))
			{
				write_some(std::move(data));
			}
		}
	}

	void stop()	//always called from the asio-service-thread
	{
		Rserial_set_->erase(shared_from_this());

		CASPAR_LOG(info) << print() << L" Client " << isopen() << L" disconnected (" << Rserial_set_->size() << L" Rserials).";

		try
		{
			fd_->cancel();
			fd_->close();
		}
		catch(...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}
	}

	Rserial(const std::shared_ptr<boost::asio::io_service>& service, 
		unsigned short port, 
		const protocol_strategy_factory<char>::ptr& protocol_factory, const spl::shared_ptr<Rserial_set>& Rserial_set)
		:protocol_factory_(protocol_factory)
		, is_writing_(false)
		, service_(service)
		, Rserial_set_(Rserial_set)
		,port_(port)
	{
		char combuf[100] = { 0 };
		sprintf(combuf, "COM%d", port_);
		fd_ = new serial_port(*service_,combuf);
		CASPAR_LOG(info) << print() << L" Accepted Rserial from " << isopen() << L" (" << (Rserial_set_->size() + 1) << L" Rserials).";
    }
			
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred) 	//always called from the asio-service-thread
	{		
		if(!error)
		{
			try
			{
				std::string data(data_.begin(), data_.begin() + bytes_transferred);
				std::string datasource;
				char buf[10] = {0};
				for (int i = 0;i<data.size();i++)
				{
					unsigned char atd = data.at(i);
					if ((atd &0xF0)>=0x0F)
						sprintf(buf, "%2x", atd);
					else
						sprintf(buf, "0%x", atd);
					datasource.append(buf);
				}
				datasource.append("\r\n");
				protocol_->parse(datasource);
			}
			catch(...)
			{
				CASPAR_LOG_CURRENT_EXCEPTION();
			}
			
			read_some();
		}  
		else if (error != boost::asio::error::operation_aborted)
			stop();		
    }

    void handle_write(const spl::shared_ptr<std::string>& str, const boost::system::error_code& error, size_t bytes_transferred)	//always called from the asio-service-thread
	{
		if(!error)
		{
			if(bytes_transferred != str->size())
			{
				str->assign(str->substr(bytes_transferred));
				fd_->async_write_some(boost::asio::buffer(str->data(), str->size()), std::bind(&Rserial::handle_write, shared_from_this(), str, std::placeholders::_1, std::placeholders::_2));
			}
			else
			{
				is_writing_ = false;
				do_write();
			}
		}
 		else if (error != boost::asio::error::operation_aborted && fd_->is_open())		
 			stop();
    }

	void read_some()	//always called from the asio-service-thread
	{
		fd_->async_read_some(boost::asio::buffer(data_.data(), data_.size()), std::bind(&Rserial::handle_read, shared_from_this(), std::placeholders::_1, std::placeholders::_2));
	}

	void write_some(std::string&& data)	//always called from the asio-service-thread
	{
		is_writing_ = true;
		auto str = spl::make_shared<std::string>(std::move(data));
		fd_->async_write_some(boost::asio::buffer(str->data(), str->size()), std::bind(&Rserial::handle_write, shared_from_this(), str, std::placeholders::_1, std::placeholders::_2));
	}
	void call_handle()
	{
		//There can use deadline_timer to cancle serial_port read data  

		//Wait for call callback function  
		service_->run();
	}
	friend struct AsyncEventServer_Serial::implementation;
};

struct AsyncEventServer_Serial::implementation : public spl::enable_shared_from_this<implementation>
{
	std::shared_ptr<boost::asio::io_service>	service_;
	
	unsigned short								port_;
	protocol_strategy_factory<char>::ptr		protocol_factory_;
	spl::shared_ptr<Rserial_set>				Rserial_set_;
	std::vector<serial_lifecycle_factory_t>		serial_lifecycle_factories_;
	tbb::mutex									mutex_;
	char										buf[1000];
	implementation(std::shared_ptr<boost::asio::io_service> service, 
		const protocol_strategy_factory<char>::ptr& protocol, 
		unsigned short port)
		: service_(std::move(service))
		, protocol_factory_(protocol)
		,port_(port)
	{
		memset(buf,0,1000);
	}

	void stop()
	{
		try
		{
		}
		catch (...)
		{
			CASPAR_LOG_CURRENT_EXCEPTION();
		}
	}

	~implementation()
	{
		auto conns_set = Rserial_set_;

		service_->post([conns_set]
		{
			auto Rserials = *conns_set;
			for (auto& Rserial : Rserials)
				Rserial->stop();
		});
	}
		
	void start()
	{
		try
		{
			auto conn = Rserial::create(service_,
				port_,
				protocol_factory_, Rserial_set_);
			Rserial_set_->insert(conn);
			for (auto& lifecycle_factory : serial_lifecycle_factories_)
			{
				auto lifecycle_bound = lifecycle_factory(u8(conn->isopen()));
				conn->add_lifecycle_bound_object(lifecycle_bound.first, lifecycle_bound.second);
			}
		}
		catch (... )
		{
			//CASPAR_LOG_CURRENT_EXCEPTION();
			CASPAR_LOG(error) << L"serial failed,Please check the serial port! " ;
		}
		
	}

	std::wstring print() const
	{
		return L"async_event_server[:" + boost::lexical_cast<std::wstring>(port_) + L"]";
	}

	void add_client_lifecycle_object_factory(const serial_lifecycle_factory_t& factory)
	{
		auto self = shared_from_this();
		service_->post([=]{ self->serial_lifecycle_factories_.push_back(factory); });
	}
};

AsyncEventServer_Serial::AsyncEventServer_Serial(
	std::shared_ptr<boost::asio::io_service> service,
	const protocol_strategy_factory<char>::ptr& protocol,
	unsigned short port)
	:impl_(new implementation(std::move(service), protocol, port))
{
	impl_->start();
}

AsyncEventServer_Serial::~AsyncEventServer_Serial()
{
	impl_->stop();
}

void AsyncEventServer_Serial::add_client_lifecycle_object_factory(const serial_lifecycle_factory_t& factory) { impl_->add_client_lifecycle_object_factory(factory); }

}}
