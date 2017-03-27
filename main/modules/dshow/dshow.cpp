//
// Created by zibj 2016/10/25.
//

#include "dshow.h"

#include "consumer/dshow_consumer.h"
#include <core/consumer/frame_consumer.h>

namespace caspar {	namespace dshow	{

	void init(core::module_dependencies dependencies)
	{
		dependencies.consumer_registry->register_consumer_factory(L"DShow Consumer", create_consumer, describe_consumer);
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"DirectShow", create_preconfigured_consumer);
	}

}}