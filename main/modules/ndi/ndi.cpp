//
// Created by zibj 2016/10/25.
//

#include "ndi.h"

#include "consumer/ndi_consumer.h"
#include "producer/ndi_producer.h"
#include <core/consumer/frame_consumer.h>
#include <Processing.NDI.Lib.h>
namespace caspar {	namespace ndi	{

	void init(core::module_dependencies dependencies)
	{
		if (!NDIlib_initialize())
		{
			CASPAR_LOG(error) << L"Cannot run NDI.";
			return;
		}
		dependencies.consumer_registry->register_consumer_factory(L"NDI Consumer", create_consumer, describe_consumer);
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"ndi", create_preconfigured_consumer);
		dependencies.producer_registry->register_producer_factory(L"Ndi Producer", create_producer, describe_producer);
	}

}}