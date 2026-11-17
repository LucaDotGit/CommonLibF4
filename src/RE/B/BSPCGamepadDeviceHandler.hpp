#pragma once

#include "RE/B/BSGamepadDevice.hpp"

namespace RE
{
	class BSPCGamepadDeviceDelegate;

	class __declspec(novtable) BSPCGamepadDeviceHandler : public BSGamepadDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCGamepadDeviceHandler;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCGamepadDeviceHandler;

		// override (BSGamepadDevice)
		void Initialize() override;				   // 0x00
		void Poll(DeltaTime a_deltaTime) override; // 0x01
		void Shutdown() override;				   // 0x02
		~BSPCGamepadDeviceHandler() override;	   // 0x04
		void ClearInputState() override;		   // 0x05
		void RestoreDirectionRepeatRates(REX::Float32 a_shortRate, REX::Float32 a_longRate, bool a_leftTrigger)
			override;															  // 0x06
		void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color) override; // 0x07
		void ResetDeviceLight() override;										  // 0x08

		virtual void FindConnectedGamepadID(); // 0x0C

		// members
		BSPCGamepadDeviceDelegate* currPCGamepadDelegate; // 0xB0
	};

	static_assert(sizeof(BSPCGamepadDeviceHandler) == 0xB8);
}
