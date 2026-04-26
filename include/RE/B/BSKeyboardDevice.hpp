#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"

namespace RE
{
	class __declspec(novtable) BSKeyboardDevice
		: public BSInputDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSKeyboardDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSKeyboardDevice };
		inline static constexpr auto DEVICE_TYPE{ INPUT_DEVICE::kKeyboard };

		// override(BSInputDevice)
		~BSKeyboardDevice() override; // 04
	};
	static_assert(sizeof(BSKeyboardDevice) == 0x70);
}
