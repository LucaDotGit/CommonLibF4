#pragma once

#include "RE/B/BSInputDevice.hpp"
#include "RE/I/INPUT_DEVICE.hpp"

namespace RE
{
	class __declspec(novtable) BSMouseDevice
		: public BSInputDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSMouseDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSMouseDevice };
		inline static constexpr auto DEVICE_TYPE{ INPUT_DEVICE::kMouse };

		// override(BSInputDevice)
		~BSMouseDevice() override; // 04
	};
	static_assert(sizeof(BSMouseDevice) == 0x70);
}
