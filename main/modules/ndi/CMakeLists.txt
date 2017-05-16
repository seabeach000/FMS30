cmake_minimum_required (VERSION 2.6)
project (ndi)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		ndi.cpp
		producer/ndi_producer.cpp
		consumer/ndi_consumer.cpp
)
set(HEADERS
		ndi.h
		producer/ndi_producer.h
		consumer/ndi_consumer.h
)

add_library(ndi ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${DTAPI_INCLUDE_PATH})
include_directories(${NDI_INCLUDE_PATH})
set_target_properties(ndi PROPERTIES FOLDER modules)
source_group(sources ./*)
if (MSVC)
	target_link_libraries(ndi
			common
			core
			ffmpeg
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(ndi
			common
			core
			ffmpeg
			x86_64-linux-gnu-4.7
			dl
			pthread
			
	)
endif ()

casparcg_add_include_statement("modules/ndi/ndi.h")
casparcg_add_init_statement("ndi::init" "ndi")
casparcg_add_module_project("ndi")
