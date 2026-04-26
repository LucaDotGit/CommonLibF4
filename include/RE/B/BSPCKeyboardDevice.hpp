#pragma once

#include "RE/B/BSKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCKeyboardDevice
		: public BSKeyboardDevice // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCKeyboardDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSPCKeyboardDevice };

		// override(BSKeyboardDevice)
		void Initialize() override;					  // 00
		void Poll(REX::Float32 a_deltaTime) override; // 01
		void Shutdown() override;					  // 02
		bool IsConnected() const override;			  // 03
		~BSPCKeyboardDevice() override;				  // 04
		void ClearInputState() override;			  // 05

		// members
		std::array<bool, REX::W32::VK_TOTAL> prevKeyStates; // 070
		std::array<bool, REX::W32::VK_TOTAL> currKeyStates; // 170
	};
	static_assert(sizeof(BSPCKeyboardDevice) == 0x270);
}
