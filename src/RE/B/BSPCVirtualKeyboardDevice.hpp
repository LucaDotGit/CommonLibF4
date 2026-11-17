#pragma once

#include "RE/B/BSVirtualKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCVirtualKeyboardDevice : public BSVirtualKeyboardDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCVirtualKeyboardDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCVirtualKeyboardDevice;

		// override (BSVirtualKeyboardDevice)
		void Initialize() override;											// 0x00
		void Poll(DeltaTime a_deltaTime) override;							// 0x01
		void Shutdown() override;											// 0x02
		~BSPCVirtualKeyboardDevice() override;								// 0x04
		void ClearInputState() override;									// 0x05
		void Start(const BSVirtualKeyboardDevice::kbInfo& a_info) override; // 0x06
		void Stop() override;												// 0x07
		void UserCancelled() override;										// 0x08
	};

	static_assert(sizeof(BSPCVirtualKeyboardDevice) == 0x70);
}
