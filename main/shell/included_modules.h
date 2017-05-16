/*
 * Generated file.
 */

#pragma once

#include <common/log.h>

#include <core/module_dependencies.h>

#include <modules/reroute/reroute.h>
#include <modules/ffmpeg/ffmpeg.h>
#include <modules/oal/oal.h>
#include <modules/bluefish/bluefish.h>
#include <modules/decklink/decklink.h>
#include <modules/screen/screen.h>
#include <modules/html/html.h>
#include <modules/psd/psd_scene_producer.h>
#include <modules/flash/flash.h>
#include <modules/newtek/newtek.h>
#include <modules/image/image.h>
#if defined(_MSC_VER)
#include <modules/dshow/dshow.h>//add by zibj 20161027
#include <modules/ndi/ndi.h>
#include <modules/matrox/matrox.h>
#endif
#include <modules/mainconcept/mainconcept.h>//add by zibj 20170210

namespace caspar {

static bool intercept_command_line_args(int argc, char** argv)
{
	if (html::intercept_command_line(argc, argv))
		return true;

	return false;
}

static void initialize_modules(const core::module_dependencies& dependencies)
{
	reroute::init(dependencies);
	CASPAR_LOG(info) << L"Initialized reroute module.";

	ffmpeg::init(dependencies);
	CASPAR_LOG(info) << L"Initialized ffmpeg module.";

	oal::init(dependencies);
	CASPAR_LOG(info) << L"Initialized oal module.";

	bluefish::init(dependencies);
	CASPAR_LOG(info) << L"Initialized bluefish module.";

	decklink::init(dependencies);
	CASPAR_LOG(info) << L"Initialized decklink module.";

	screen::init(dependencies);
	CASPAR_LOG(info) << L"Initialized screen module.";

	html::init(dependencies);
	CASPAR_LOG(info) << L"Initialized html module.";

	psd::init(dependencies);
	CASPAR_LOG(info) << L"Initialized psd module.";

	flash::init(dependencies);
	CASPAR_LOG(info) << L"Initialized flash module.";

	newtek::init(dependencies);
	CASPAR_LOG(info) << L"Initialized newtek module.";

	image::init(dependencies);
	CASPAR_LOG(info) << L"Initialized image module.";
#if defined(_MSC_VER)
	dshow::init(dependencies);
	CASPAR_LOG(info) << L"Initialized dshow module.";

	ndi::init(dependencies);
	CASPAR_LOG(info) << L"Initialized ndi module.";

	matrox::init(dependencies);
	CASPAR_LOG(info) << L"Initialized matrox module.";
#endif
	mainconcept::init(dependencies);
	CASPAR_LOG(info) << L"Initialized mainconcept module.";
}

static void uninitialize_modules()
{
	image::uninit();
	html::uninit();
	ffmpeg::uninit();
}

}
