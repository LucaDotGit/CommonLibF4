#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class MovementActorAvoidanceParameters
	{
	public:
		enum class Flags : std::uint32_t; // To-Do

		// members
		BSTSmallArray<std::uint32_t, 1> actors;	  // 0x00
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x18
	};

	static_assert(sizeof(MovementActorAvoidanceParameters) == 0x20);
}
