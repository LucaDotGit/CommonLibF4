#pragma once

namespace RE
{
	class BSPathingSearchParameters
	{
	public:
		enum class Flags : std::uint16_t
		{
			None = 0,
			AllowIncompletePath = 1 << 0,
			GoDirectIfPathingFails = 1 << 1,
			IgnoreSmoothingIfFails = 1 << 2,
			UsePreferredPath = 1 << 3,
			RequiresHavok = 1 << 4,
			AvoidPreferredPath = 1 << 5,
			MustQueue = 1 << 6,
			CanShortcut = 1 << 7,
			AllowUnattachedCell = 1 << 8,
			ProcessSynchronously = 1 << 9,
			ResolveGoalToClosest = 1 << 10
		};

		// members
		REX::Float32 preferredCostFactor;		  // 0x00
		REX::Float32 tangentSmoothingFactor;	  // 0x04
		std::uint16_t retryCount;				  // 0x08
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x0A
	};

	static_assert(sizeof(BSPathingSearchParameters) == 0x0C);
}
