#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.hpp"

namespace RE
{
	class __declspec(novtable) BSPCGamepadDevice : public BSPCGamepadDeviceDelegate // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCGamepadDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCGamepadDevice;

		// override (BSPCGamepadDeviceDelegate)
		void Initialize() override;				   // 0x00
		void Poll(DeltaTime a_deltaTime) override; // 0x01
		void Shutdown() override;				   // 0x02
		~BSPCGamepadDevice() override;			   // 0x04

		// members
		GamepadState<REX::W32::XINPUT_STATE> prevState; // 0xB8
		GamepadState<REX::W32::XINPUT_STATE> currState; // 0xE0
	};

	static_assert(sizeof(BSPCGamepadDevice) == 0x108);
}
