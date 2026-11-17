#pragma once

#include "RE/B/BSPathingLocation.hpp"

namespace RE
{
	class BSPathingStart
	{
	public:
		enum class START_TANGENT_TYPE : std::int32_t
		{
			None = 0,
			Set = 1,
			Keep = 2,
			Mask = 3
		};

		enum class FLAGS : std::uint32_t
		{
			Selected = 0,
			StartsMoving = 1 << 0
		};

		// members
		BSPathingLocation location;							  // 0x00
		REX::Float32 tangent{static_cast<REX::Float32>(0.0)}; // 0x30
	};

	static_assert(sizeof(BSPathingStart) == 0x38);
}
