//
// Created by zibj 2017/02/09.
//

#include "mainconcept_consumer.h"

#include <common/memcpy.h>
#include <common/future.h>
#include <common/param.h>
#include <common/ptree.h>
#include <common/os/general_protection_fault.h>
#include <common/diagnostics/graph.h>
#include <common/env.h>
#include <common/executor.h>

#include <core/video_format.h>
#include <core/frame/frame.h>
#include <core/frame/audio_channel_layout.h>
#include <core/consumer/frame_consumer.h>
#include <core/help/help_sink.h>

#include <tbb/atomic.h>
#include <tbb/concurrent_queue.h>
#include <tbb/parallel_for.h>
#include <tbb/mutex.h>

#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>

#pragma warning(push)
#pragma warning(disable: 4244)
#pragma warning(disable: 4245)
#include <boost/crc.hpp>
#pragma warning(pop)

#include <vector>

#include "../mc_enc_pumpstream.h"


namespace caspar {
	namespace mainconcept {

		struct mainconcept_consumer : boost::noncopyable
 		{
			const spl::shared_ptr<diagnostics::graph>			graph_;
			caspar::timer										tick_timer_;

			core::monitor::subject								subject_;
			std::string											path_;
			boost::filesystem::path                             full_path_;
			std::map<std::string, std::string>					options_;

			core::video_format_desc								in_video_format_;
			core::audio_channel_layout							in_channel_layout_ = core::audio_channel_layout::invalid();

			tbb::atomic<bool>									is_running_;
  			tbb::concurrent_bounded_queue<core::const_frame>	frame_buffer_;

			boost::thread										thread_;

			mc_enc_pumpstream*                                  enc_pumpstream = nullptr;
			
			executor									video_encoder_executor_;
			executor									audio_encoder_executor_;

		public:

			std::future<bool> send(core::const_frame frame)
			{
				graph_->set_value("tick-time", tick_timer_.elapsed()*in_video_format_.fps*0.5);
 				if (!frame_buffer_.try_push(frame))
 					graph_->set_tag(diagnostics::tag_severity::WARNING, "dropped-frame");
  				graph_->set_text(print());
 				graph_->set_value("buffer-frames", ((double)frame_buffer_.size()) / frame_buffer_.capacity());
 				tick_timer_.restart();
 
 				return make_ready_future(is_running_.load());
			}
		
			std::wstring print() const
			{
				return L"mainconcept_consumer[" + u16(path_) + L"|" + boost::lexical_cast<std::wstring>(frame_buffer_.size()) + L"]";
			}

			mainconcept_consumer(
				std::string path,
				std::string options)
				:path_(path)
				,full_path_(path)
				, audio_encoder_executor_(print() + L" audio_encoder")
				, video_encoder_executor_(print() + L" video_encoder")
  			{
				frame_buffer_.set_capacity(4);
				is_running_ = true;

				options = boost::to_lower_copy(options);

				for (auto it =
					boost::sregex_iterator(
						options.begin(),
						options.end(),
						boost::regex("-(?<NAME>[^-\\s]+)(\\s+(?<VALUE>[^\\s]+))?"));
					it != boost::sregex_iterator();
					++it)
				{
					options_[(*it)["NAME"].str()] = (*it)["VALUE"].matched ? (*it)["VALUE"].str() : "";
				}
 			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout)
			{
				in_video_format_ = format_desc;
				in_channel_layout_ = channel_layout;

				graph_->set_color("tick-time", diagnostics::color(0.0f, 0.6f, 0.9f));
				graph_->set_color("pushframe-time", diagnostics::color(0.1f, 1.0f, 0.1f));
				graph_->set_color("dropped-frame", diagnostics::color(0.3f, 0.6f, 0.3f));
				graph_->set_color("buffer-frames", diagnostics::color(0.7f, 0.4f, 0.4f));
				graph_->set_text(print());
				diagnostics::register_graph(graph_);

				bool is_output_stream = path_parser(); //output stream or record file

				enc_pumpstream = new mc_enc_pumpstream(in_video_format_, in_channel_layout_, is_output_stream);
				if (true == enc_pumpstream->initialize(options_, full_path_.string()))
				{
					thread_ = boost::thread([this] {run(); });
				}
			}

			////output stream or record file,record file uses absolute path.
			bool path_parser()
			{
				bool is_output_stream = true;
				static boost::regex prot_exp("^.+:.*");
				static boost::regex prot_exp_disk("^.{1}:.*");
				if (!boost::regex_match(path_,prot_exp))//relative path
				{
					if (!full_path_.is_complete())
					{
						full_path_ =
							u8(
								env::media_folder()) +
							path_;
					}
					if (boost::filesystem::is_directory(full_path_))
					{
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"the complete path [" + u16(full_path_.string()) + L"] is not a file path."));
					}
					else if(boost::filesystem::exists(full_path_))
						boost::filesystem::remove(full_path_);
					boost::filesystem::create_directories(full_path_.parent_path());
					is_output_stream = false;
				}
				else if (boost::regex_match(path_, prot_exp_disk))//absolute path
				{
					if (boost::filesystem::is_directory(full_path_))
					{
						CASPAR_THROW_EXCEPTION(user_error() << msg_info(L"the complete path [" + u16(full_path_.string()) + L"] is not a file path."));
					}
					else if (boost::filesystem::exists(full_path_))
						boost::filesystem::remove(full_path_);
					boost::filesystem::create_directories(full_path_.parent_path());
					is_output_stream = false;
				}

				return is_output_stream;
			}
  
			void run()
 			{
				ensure_gpf_handler_installed_for_thread(
					"mainconcept-consumer-thread");
				caspar::timer pushframe_timer;
				while (is_running_)
				{
					core::const_frame frame;
					if (!frame_buffer_.try_pop(frame))
					{
						boost::this_thread::sleep_for(boost::chrono::milliseconds(1));
						continue;
					}
					pushframe_timer.restart();
					video_encoder_executor_.begin_invoke([=]() mutable
					{
						enc_pumpstream->encode_video(frame);
					});

					audio_encoder_executor_.begin_invoke([=]() mutable
					{
						enc_pumpstream->encode_audio(frame);
					});
					graph_->set_value("pushframe-time", pushframe_timer.elapsed() * in_video_format_.fps * 0.5);
				}
 			}

   			~mainconcept_consumer()
 			{
				video_encoder_executor_.stop();
				audio_encoder_executor_.stop();
				video_encoder_executor_.join();
				audio_encoder_executor_.join();

				is_running_ = false;
				thread_.join();
				if (enc_pumpstream)
				{
					delete enc_pumpstream;
					enc_pumpstream = nullptr;
				}

			}

			core::monitor::subject& monitor_output()
			{
				return subject_;
			}
		};

		int crc16(const std::string& str)
		{
			boost::crc_16_type result;

			result.process_bytes(str.data(), str.length());

			return result.checksum();
		}
		struct mainconcept_consumer_proxy : public core::frame_consumer
		{
			const std::string						path_;
			const std::string						options_;

			int									consumer_index_offset_;

 			std::unique_ptr<mainconcept_consumer> consumer_;
 		public:
			mainconcept_consumer_proxy(const std::string& path, const std::string& options)
				:path_(path)
				,options_(options)
				, consumer_index_offset_(crc16(path))
			{
			}

			// Methods
			std::future<bool> send(core::const_frame frame) override
			{
				return consumer_->send(frame);
			}
			void initialize(
				const core::video_format_desc& format_desc,
				const core::audio_channel_layout& channel_layout,
				int channel_index) override
			{
				if (consumer_)
					CASPAR_THROW_EXCEPTION(invalid_operation() << msg_info("Cannot reinitialize mainconcept-consumer."));
				consumer_.reset(new mainconcept_consumer(path_, options_));
				consumer_->initialize(format_desc, channel_layout);
			}

			// monitor::observable
			core::monitor::subject& monitor_output() override
			{
				return consumer_->monitor_output();
			}
			
			// Properties

			std::wstring print() const override
			{
				return consumer_ ? consumer_->print() : L"[mainconcept_consumer]";
			}

			std::wstring name() const override
			{
				return L"mainconcept";
			}

			boost::property_tree::wptree info() const override
			{
				boost::property_tree::wptree info;
				info.add(L"type", L"mainconcept");
				info.add(L"path", u16(path_));
				return info;
			}

			bool has_synchronization_clock() const override
			{
				return false;
			}

			int buffer_depth() const override// -1 to not participate in frame presentation synchronization
			{
				return 2;
			}

			int index() const override
			{
				return 8000 + consumer_index_offset_;
			}

			int64_t presentation_frame_age_millis() const override
			{
				return 1;
			}
		};

		void describe_consumer(core::help_sink& sink, const core::help_repository& repo)
		{
			sink.short_description(L"Mainconcept Consumer.");
			sink.para()->text(L"Examples:");
			sink.example(L">> ADD 1 MAINCONCEPT output.ts -format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134");
			sink.example(L">> ADD 1 MAINCONCEPT e:/output.ts -format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134");
			sink.example(L">> ADD 1 MAINCONCEPT udp://234.5.5.1:2345 -format mpegts -vcodec mpeg2 -acodec aac -vbitrate 8000000 -pcrinterval 30 -psiinterval 100 -videopid 1234 -audiopid 2134");
			sink.example(L">> REMOVE 1 MAINCONCEPT udp://234.5.5.1:2345");
			sink.example(L">> REMOVE 1 MAINCONCEPT e:/output.ts");
			sink.example(L">> REMOVE 1 MAINCONCEPT output.ts");
		}

		spl::shared_ptr<core::frame_consumer> create_consumer(
			const std::vector<std::wstring>& params, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			if (params.size() < 1 || !boost::iequals(params.at(0), L"MAINCONCEPT"))
				return core::frame_consumer::empty();
			auto params2 = params;
			auto path = u8(params2.size() > 1 ? params2.at(1) : L"");
			auto args = u8(boost::join(params2, L" "));

			return spl::make_shared<mainconcept_consumer_proxy>(path,args);
		}

		spl::shared_ptr<core::frame_consumer> create_preconfigured_consumer(
			const boost::property_tree::wptree& ptree, core::interaction_sink* sink, std::vector<spl::shared_ptr<core::video_channel>> channels)
		{
			return spl::make_shared<mainconcept_consumer_proxy>(
				u8(ptree_get<std::wstring>(ptree, L"path")),
				u8(ptree.get<std::wstring>(L"args", L"")));
		}
}}




