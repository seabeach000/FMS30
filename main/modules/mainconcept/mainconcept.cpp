//
// Created by zibj 2017/02/09.
//

#include "mainconcept.h"

#include "consumer/mainconcept_consumer.h"
#include <core/consumer/frame_consumer.h>

namespace caspar {	namespace mainconcept {

	void init(core::module_dependencies dependencies)
	{
		dependencies.consumer_registry->register_consumer_factory(L"Mainconcept Consumer", create_consumer, describe_consumer);
		dependencies.consumer_registry->register_preconfigured_consumer_factory(L"mainconcept", create_preconfigured_consumer);
	}

}}