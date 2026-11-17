#pragma once

#include "RE/I/InputEvent.hpp"

namespace RE
{
	class __declspec(novtable) DeviceConnectEvent : public InputEvent // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::DeviceConnectEvent;
		inline static constexpr const auto& VTABLE = VTABLE::DeviceConnectEvent;
		inline static constexpr auto INPUT_TYPE = INPUT_EVENT_TYPE::DeviceConnect;

		~DeviceConnectEvent() override = default; // 0x00

		// members
		bool connected{true}; // 0x28
	};

	static_assert(sizeof(DeviceConnectEvent) == 0x30);
}
