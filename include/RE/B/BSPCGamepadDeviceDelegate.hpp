#pragma once

#include "RE/B/BSGamepadDevice.hpp"

namespace RE
{
	class BSPCGamepadDeviceHandler;

	class __declspec(novtable) BSPCGamepadDeviceDelegate
		: public BSGamepadDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCGamepadDeviceDelegate };
		inline static constexpr auto VTABLE{ VTABLE::BSPCGamepadDeviceDelegate };

		// override (BSGamepadDevice)
		void Initialize() override;					  // 00
		void Poll(REX::Float32 a_deltaTime) override; // 01
		void Shutdown() override;					  // 02
		~BSPCGamepadDeviceDelegate() override;		  // 04
		void ClearInputState() override;			  // 05

		// members
		BSPCGamepadDeviceHandler* gamepadDeviceHandler; // B0
	};
	static_assert(sizeof(BSPCGamepadDeviceDelegate) == 0xB8);
}
