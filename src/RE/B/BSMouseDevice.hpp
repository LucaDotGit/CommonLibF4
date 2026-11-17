#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"

namespace RE
{
	class __declspec(novtable) BSMouseDevice : public BSInputDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSMouseDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSMouseDevice;
		inline static constexpr auto DEVICE_TYPE = INPUT_DEVICE::Mouse;

		// override (BSInputDevice)
		~BSMouseDevice() override; // 0x04
	};

	static_assert(sizeof(BSMouseDevice) == 0x70);
}
