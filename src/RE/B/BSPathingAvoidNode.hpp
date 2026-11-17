#pragma once

#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSPathingAvoidNode
	{
	public:
		enum class AVOID_NODE_TYPE : std::int32_t
		{
			Sphere = 0,
			Cylinder = 1,
			SphereActor = 2,
			SphereTarget = 3,
			SphereThreat = 4,
			SphereObstacle = 5
		};

		// members
		NiPoint3 point01;							   // 0x00
		NiPoint3 point02;							   // 0x0C
		REX::Float32 radius;						   // 0x18
		REX::Float32 cost;							   // 0x1C
		REX::Enum<AVOID_NODE_TYPE, std::int32_t> type; // 0x20
	};

	static_assert(sizeof(BSPathingAvoidNode) == 0x24);
}
