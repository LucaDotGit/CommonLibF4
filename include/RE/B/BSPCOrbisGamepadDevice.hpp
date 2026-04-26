#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.hpp"
#include "RE/S/ScePadData.hpp"

namespace RE
{
	class __declspec(novtable) BSPCOrbisGamepadDevice
		: public BSPCGamepadDeviceDelegate // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCOrbisGamepadDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSPCOrbisGamepadDevice };

		// override(BSPCGamepadDeviceDelegate)
		void Initialize() override;																						  // 00
		void Poll(REX::Float32 a_deltaTime) override;																	  // 01
		void Shutdown() override;																						  // 02
		~BSPCOrbisGamepadDevice() override;																				  // 04
		void ClearInputState() override;																				  // 05
		void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color) override;										  // 07
		void ResetDeviceLight() override;																				  // 08
		void NormalizeThumbstickValue(REX::Float32 a_xHardware, REX::Float32 a_yHardware, REX::Float32& a_xOut) override; // 0A

		// members
		GamepadState<ScePadData> prevState; // 0B8
		GamepadState<ScePadData> currState; // 148
	};
	static_assert(sizeof(BSPCOrbisGamepadDevice) == 0x1D8);
}
