#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.hpp"

namespace RE
{
	class __declspec(novtable) BSPCGamepadDevice
		: public BSPCGamepadDeviceDelegate // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCGamepadDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSPCGamepadDevice };

		// override(BSPCGamepadDeviceDelegate)
		void Initialize() override;					  // 00
		void Poll(REX::Float32 a_deltaTime) override; // 01
		void Shutdown() override;					  // 02
		~BSPCGamepadDevice() override;				  // 04

		// members
		GamepadState<REX::W32::XINPUT_STATE> prevState; // B8
		GamepadState<REX::W32::XINPUT_STATE> currState; // E0
	};
	static_assert(sizeof(BSPCGamepadDevice) == 0x108);
}
