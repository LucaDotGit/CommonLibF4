#pragma once

namespace RE::MovementLargeDelta
{
	enum class SPEED : std::int32_t;
	enum class FROM_DIRECTION : std::int32_t;

	class CurrentState
	{
	public:
		// members
		REX::Enum<SPEED, std::int32_t> fromSpeed;			   // 0x00
		REX::Enum<FROM_DIRECTION, std::int32_t> fromDirection; // 0x04
	};

	static_assert(sizeof(CurrentState) == 0x08);
}
