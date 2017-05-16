cmake_minimum_required (VERSION 2.6)
project (mainconcept)

#set(CMAKE_C_COMPILER g++)	# 更规范c源代码

set(SOURCES
		bufstream/buf_fifo.c
		bufstream/buf_file.c
		bufstream/sr_fifo.c

		consumer/mainconcept_consumer.cpp

		DtNetRender.cpp
		mainconcept.cpp
		mc_enc_pumpstream.cpp
		MCNetRender.cpp
)
set(HEADERS
		bufstream/buf_fifo.h
		bufstream/buf_file.h
		bufstream/sr_fifo.h

		consumer/mainconcept_consumer.h

		DtNetRender.h
		mainconcept.h
		mc_enc_pumpstream.h
		MCNetRender.h
		params.h
		mc_os_common.h
)

add_library(mainconcept ${SOURCES} ${HEADERS})

include_directories(..)
include_directories(../..)
include_directories(${BOOST_INCLUDE_PATH})
include_directories(${TBB_INCLUDE_PATH})
include_directories(${FFMPEG_INCLUDE_PATH})
include_directories(${RXCPP_INCLUDE_PATH})
include_directories(${ASMLIB_INCLUDE_PATH})
include_directories(${DTAPI_INCLUDE_PATH})
include_directories(${MAINCONCEPT_INCLUDE_PATH})

set_target_properties(mainconcept PROPERTIES FOLDER modules)
source_group(sources ./*)
source_group(sources\\bufstream bufstream/*)
source_group(sources\\consumer consumer/*)

if (MSVC)
	target_link_libraries(mainconcept
			common
			core
			ffmpeg
			
			bc_net_renderer.lib
			parser_sdp.lib
			net_tools.lib
			enc_avc.lib
			enc_mp2v.lib
			enc_mpa.lib
			enc_pcm.lib
			enc_aac.lib
			mux_mp2.lib
	)
elseif (CMAKE_COMPILER_IS_GNUCXX)
	target_link_libraries(mainconcept
			common
			core
			ffmpeg

			dtapi64
			#mc_crypto
			#mc_ssl

			-Wl,--start-group
			demo_bc_net_renderer
			demo_parser_sdp
			demo_net_tools
			mc_config_avc
			mc_enc_avc
			demo_enc_mp2v
			demo_enc_mpa
			mc_enc_pcm
			mc_enc_aac
			#mc_demux_mp4
			#mc_demux_mp2
			mc_mux_mp2
			#demo_stream_pump
			#demo_trans_video_colorspace
			
			-Wl,--end-group

			pthread
			dl
	)
endif ()

if(MSVC)
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_bc_net_renderer.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_avc.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_mp2v.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_config_mpa.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_net_tools.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_aac.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_avc.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_mp2v.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_mpa.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_enc_pcm.dll")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/mc_mux_mp2.dll")
else ()
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_bc_net_renderer.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_enc_mp2v.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_enc_mpa.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_net_tools.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libdemo_parser_sdp.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_config_avc.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_aac.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_avc.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_enc_pcm.so")
	casparcg_add_runtime_dependency("${MAINCONCEPT_BIN_PATH}/libmc_mux_mp2.so")
endif ()

casparcg_add_include_statement("modules/mainconcept/mainconcept.h")
casparcg_add_init_statement("mainconcept::init" "mainconcept")
casparcg_add_module_project("mainconcept")
