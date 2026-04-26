#pragma once

#include "RE/B/BSGamepadDevice.hpp"

namespace RE
{
	class BSPCGamepadDeviceDelegate;

	class __declspec(novtable) BSPCGamepadDeviceHandler
		: public BSGamepadDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCGamepadDeviceHandler };
		inline static constexpr auto VTABLE{ VTABLE::BSPCGamepadDeviceHandler };

		// override(BSGamepadDevice)
		void Initialize() override;																						  // 00
		void Poll(REX::Float32 a_deltaTime) override;																	  // 01
		void Shutdown() override;																						  // 02
		~BSPCGamepadDeviceHandler() override;																			  // 04
		void ClearInputState() override;																				  // 05
		void RestoreDirectionRepeatRates(REX::Float32 a_shortRate, REX::Float32 a_longRate, bool a_leftTrigger) override; // 06
		void SetDeviceLight(const std::array<std::uint8_t, 3>& a_color) override;										  // 07
		void ResetDeviceLight() override;																				  // 08

		virtual void FindConnectedGamepadID(); // 0C

		// members
		BSPCGamepadDeviceDelegate* currPCGamepadDelegate; // B0
	};
	static_assert(sizeof(BSPCGamepadDeviceHandler) == 0xB8);
}
