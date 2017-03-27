//
// Created by zibj 2016/10/25.
//

#include "matrox.h"

#include "consumer/matrox_consumer.h"
#include "producer/matrox_producer.h"
#include <core/consumer/frame_consumer.h>
#include <mvHResult.h>
#include <MatroxDSXsdk.h>
namespace caspar {	namespace matrox	{
	
	void init(core::module_dependencies dependencies)
	{

		//ºÏ≤‚ «∑Ò”–¬Û¥¥ø®
		CMvHResult oHr;
		oHr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED);

		if (oHr.DidFail())
		{

			CASPAR_LOG(error) << L"matrox  : Unable to create the system configuration interface.";
			CoUninitialize();

			return ;
		}

		

		dependencies.consumer_registry->register_consumer_factory(L"Matrox Consumer", create_consumer, describe_consumer);
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"matrox", create_preconfigured_consumer);
		dependencies.producer_registry->register_producer_factory(L"Matrox Producer", create_producer, describe_producer);
	}

}}