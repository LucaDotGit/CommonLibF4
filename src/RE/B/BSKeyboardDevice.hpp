#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"

namespace RE
{
	class __declspec(novtable) BSKeyboardDevice : public BSInputDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSKeyboardDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSKeyboardDevice;
		inline static constexpr auto DEVICE_TYPE = INPUT_DEVICE::Keyboard;

		// override (BSInputDevice)
		~BSKeyboardDevice() override; // 0x04
	};

	static_assert(sizeof(BSKeyboardDevice) == 0x70);
}
