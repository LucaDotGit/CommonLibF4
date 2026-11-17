#pragma once

#include "RE/B/BSMouseDevice.hpp"

namespace RE
{
	class __declspec(novtable) BSPCMouseDevice : public BSMouseDevice // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPCMouseDevice;
		inline static constexpr const auto& VTABLE = VTABLE::BSPCMouseDevice;

		enum class ButtonFlags : std::uint8_t
		{
			None = 0,
			Left = 1 << 0,
			Right = 1 << 1,
			Middle = 1 << 2,
			Button3 = 1 << 3,
			Button4 = 1 << 4
		};

		// override (BSMouseDevice)
		void Initialize() override;				   // 0x00
		void Poll(DeltaTime a_deltaTime) override; // 0x01
		void Shutdown() override;				   // 0x02
		~BSPCMouseDevice() override;			   // 0x04

		// members
		REX::EnumSet<ButtonFlags, std::uint8_t> currButtonFlags; // 0x70
		REX::EnumSet<ButtonFlags, std::uint8_t> prevButtonFlags; // 0x71
		std::int16_t wheelDelta;								 // 0x72
		std::int32_t accumMouseMoveX;							 // 0x74
		std::int32_t accumMouseMoveY;							 // 0x78
		std::int32_t currCursorPosX;							 // 0x7C
		std::int32_t currCursorPosY;							 // 0x80
	};

	static_assert(sizeof(BSPCMouseDevice) == 0x88);
}
