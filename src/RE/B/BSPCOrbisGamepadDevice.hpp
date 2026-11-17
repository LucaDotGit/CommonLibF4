#pragma once

#include "RE/B/BSPCGamepadDeviceDelegate.hpp"
#include "RE/S/ScePadData.hpp"

namespace RE
{
	class __declspec(novtable) BSPCOrbisGamepadDevice : public BSPCGamepadDeviceDelegate // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCOrbisGamepadDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCOrbisGamepadDevice;

		// override (BSPCGamepadDeviceDelegate)
		void Initialize() override;												  // 0x00
		void Poll(DeltaTime a_deltaTime) override;								  // 0x01
		void Shutdown() override;												  // 0x02
		~BSPCOrbisGamepadDevice() override;										  // 0x04
		void ClearInputState() override;										  // 0x05
		void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color) override; // 0x07
		void ResetDeviceLight() override;										  // 0x08
		void NormalizeThumbstickValue(REX::Float32 a_xHardware, REX::Float32 a_yHardware, REX::Float32& a_xOut)
			override; // 0x0A

		// members
		GamepadState<ScePadData> prevState; // 0x0B8
		GamepadState<ScePadData> currState; // 0x148
	};

	static_assert(sizeof(BSPCOrbisGamepadDevice) == 0x1D8);
}
