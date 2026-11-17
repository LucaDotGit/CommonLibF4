#pragma once

#include "RE/B/BSInputEventUser.hpp"

namespace RE
{
	class __declspec(novtable) ScreenshotHandler : public BSInputEventUser // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ScreenshotHandler;
		inline static constexpr const auto& VTABLE = VTABLE::ScreenshotHandler;

		// members
		bool screenshotQueued;		// 0x10
		bool multiScreenshotQueued; // 0x11
	};

	static_assert(sizeof(ScreenshotHandler) == 0x18);
}
