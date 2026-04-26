#pragma once

#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) DeviceConnectEvent
		: public InputEvent // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DeviceConnectEvent };
		inline static constexpr auto VTABLE{ VTABLE::DeviceConnectEvent };
		inline static constexpr auto INPUT_TYPE{ INPUT_EVENT_TYPE::kDeviceConnect };

		~DeviceConnectEvent() override = default; // 00

		// members
		bool connected{ true }; // 28
	};
	static_assert(sizeof(DeviceConnectEvent) == 0x30);

	extern template bool InputEvent::Is<DeviceConnectEvent>() const noexcept;
	extern template bool InputEvent::IsNot<DeviceConnectEvent>() const noexcept;

	extern template DeviceConnectEvent* InputEvent::As() noexcept;
	extern template const DeviceConnectEvent* InputEvent::As() const noexcept;
}
