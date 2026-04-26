#pragma once

#include "RE/N/NiPlane.hpp"

namespace RE
{
	class NiFrustumPlanes
	{
	public:
		enum class Plane : std::int32_t
		{
			kNearPlane = 0,
			kFarPlane = 1,
			kLeftPlane = 2,
			kRightPlane = 3,
			kTopPlane = 4,
			kBottomPlane = 5
		};

		// members
		std::array<NiPlane, 6> cullingPlanes; // 00
		std::uint32_t activePlanes{ 0 };	  // 60
		std::uint32_t basePlaneStates{ 0 };	  // 64
		std::array<std::uint32_t, 2> pad68{}; // 68
	};
	static_assert(sizeof(NiFrustumPlanes) == 0x70);
}
