#pragma once

#include <core/video_format.h>

#include <common/forward.h>
#include <common/memory.h>
#include <common/cache_aligned_vector.h>
#include <common/array.h>

#include <core/frame/frame_visitor.h>
#include <core/monitor/monitor.h>

#include <vector>
#include <cstdint>
namespace caspar {
	namespace matrox {
		struct MatroxFrame {
			std::shared_ptr<uint8_t> pvideo;
			std::shared_ptr<uint8_t> paudio;
			unsigned int audiolen;
			unsigned int videolen;
			int afd_aspect_ratio_;//0 4:3  1 16:9
			int afd_command_;
			int interlaced_frame;
			int top_field_first;
			int width;
			int height;
			int usample;
		};


		class matrox_interface
		{
		public:
			matrox_interface(
				int hardwareindex,
				int audiochannel,
				int conrector,
				std::wstring ratio_s,
				core::video_format format
			);
			~matrox_interface() {}
			bool get_frame(MatroxFrame &);
		private:
			struct impl;
			spl::shared_ptr<impl> impl_;
		};

	}
}