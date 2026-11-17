#pragma once

namespace RE::MovementLargeDelta
{
	enum class SPEED : std::int32_t;
	enum class TO_DIRECTION : std::int32_t;

	class DesiredState
	{
	public:
		// members
		REX::Enum<SPEED, std::int32_t> toSpeed;			   // 0x00
		REX::Enum<TO_DIRECTION, std::int32_t> toDirection; // 0x04
	};

	static_assert(sizeof(DesiredState) == 0x08);
}
