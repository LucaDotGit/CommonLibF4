#pragma once

#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSPathingAvoidNode
	{
	public:
		enum class AVOID_NODE_TYPE : std::int32_t
		{
			kSphere = 0,
			kCylinder = 1,
			kSphereActor = 2,
			kSphereTarget = 3,
			kSphereThreat = 4,
			kSphereObstacle = 5
		};

		// members
		NiPoint3 point01;							   // 00
		NiPoint3 point02;							   // 0C
		REX::Float32 radius;						   // 18
		REX::Float32 cost;							   // 1C
		REX::Enum<AVOID_NODE_TYPE, std::int32_t> type; // 20
	};
	static_assert(sizeof(BSPathingAvoidNode) == 0x24);
}
