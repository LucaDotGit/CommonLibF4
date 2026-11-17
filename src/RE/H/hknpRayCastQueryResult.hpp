#pragma once

#include "RE/H/hknpCollisionResult.hpp"

namespace RE
{
	class hknpRayCastQueryResult : public hknpCollisionResult // 0x00
	{
	public:
	};

	static_assert(sizeof(hknpRayCastQueryResult) == 0x60);
}
