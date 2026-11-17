#pragma once

#include "RE/N/NiPlane.hpp"

namespace RE
{
	class NiFrustumPlanes
	{
	public:
		enum class Plane : std::int32_t
		{
			NearPlane = 0,
			FarPlane = 1,
			LeftPlane = 2,
			RightPlane = 3,
			TopPlane = 4,
			BottomPlane = 5
		};

		// members
		std::array<NiPlane, 6> cullingPlanes;  // 0x00
		std::uint32_t activePlanes{0};		   // 0x60
		std::uint32_t basePlaneStates{0};	   // 0x64
		std::array<std::uint32_t, 2> pad68{0}; // 0x68
	};

	static_assert(sizeof(NiFrustumPlanes) == 0x70);
}
