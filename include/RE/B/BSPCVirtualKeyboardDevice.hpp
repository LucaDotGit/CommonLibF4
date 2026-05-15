#pragma once

#include "RE/B/BSVirtualKeyboardDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCVirtualKeyboardDevice
		: public BSVirtualKeyboardDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCVirtualKeyboardDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSPCVirtualKeyboardDevice };

		// override (BSVirtualKeyboardDevice)
		void Initialize() override;											// 00
		void Poll(REX::Float32 a_deltaTime) override;						// 01
		void Shutdown() override;											// 02
		~BSPCVirtualKeyboardDevice() override;								// 04
		void ClearInputState() override;									// 05
		void Start(const BSVirtualKeyboardDevice::kbInfo& a_info) override; // 06
		void Stop() override;												// 07
		void UserCancelled() override;										// 08
	};
	static_assert(sizeof(BSPCVirtualKeyboardDevice) == 0x70);
}
