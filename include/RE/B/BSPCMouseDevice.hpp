#pragma once

#include "RE/B/BSMouseDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCMouseDevice
		: public BSMouseDevice // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPCMouseDevice };
		inline static constexpr auto VTABLE{ VTABLE::BSPCMouseDevice };

		enum class ButtonFlags : std::uint8_t
		{
			kNone = 0,
			kLeft = 1 << 0,
			kRight = 1 << 1,
			kMiddle = 1 << 2,
			kButton3 = 1 << 3,
			kButton4 = 1 << 4
		};

		// override (BSMouseDevice)
		void Initialize() override;					  // 00
		void Poll(REX::Float32 a_deltaTime) override; // 01
		void Shutdown() override;					  // 02
		~BSPCMouseDevice() override;				  // 04

		// members
		REX::EnumSet<ButtonFlags, std::uint8_t> currButtonFlags; // 70
		REX::EnumSet<ButtonFlags, std::uint8_t> prevButtonFlags; // 71
		std::int16_t wheelDelta;								 // 72
		std::int32_t accumMouseMoveX;							 // 74
		std::int32_t accumMouseMoveY;							 // 78
		std::int32_t currCursorPosX;							 // 7C
		std::int32_t currCursorPosY;							 // 80
	};
	static_assert(sizeof(BSPCMouseDevice) == 0x88);
}
