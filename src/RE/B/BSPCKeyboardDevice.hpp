#pragma once

#include "RE/B/BSKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCKeyboardDevice : public BSKeyboardDevice // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCKeyboardDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCKeyboardDevice;

		// override (BSKeyboardDevice)
		void Initialize() override;				   // 0x00
		void Poll(DeltaTime a_deltaTime) override; // 0x01
		void Shutdown() override;				   // 0x02
		auto IsConnected() const -> bool override; // 0x03
		~BSPCKeyboardDevice() override;			   // 0x04
		void ClearInputState() override;		   // 0x05

		// members
		std::array<bool, REX::W32::VK_TOTAL> prevKeyStates; // 0x070
		std::array<bool, REX::W32::VK_TOTAL> currKeyStates; // 0x170
	};

	static_assert(sizeof(BSPCKeyboardDevice) == 0x270);
}
