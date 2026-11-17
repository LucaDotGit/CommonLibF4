#pragma once

#include "RE/B/BSGamepadDevice.hpp"

namespace RE
{
	class BSPCGamepadDeviceHandler;

	class __declspec(novtable) BSPCGamepadDeviceDelegate : public BSGamepadDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCGamepadDeviceDelegate;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCGamepadDeviceDelegate;

		// override (BSGamepadDevice)
		void Initialize() override;				   // 0x00
		void Poll(DeltaTime a_deltaTime) override; // 0x01
		void Shutdown() override;				   // 0x02
		~BSPCGamepadDeviceDelegate() override;	   // 0x04
		void ClearInputState() override;		   // 0x05

		// members
		BSPCGamepadDeviceHandler* gamepadDeviceHandler; // 0xB0
	};

	static_assert(sizeof(BSPCGamepadDeviceDelegate) == 0xB8);
}
