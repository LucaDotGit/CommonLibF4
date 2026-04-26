#pragma once

#include "RE/H/hknpCollisionResult.hpp"

namespace RE
{
	class hknpRayCastQueryResult
		: public hknpCollisionResult // 00
	{
	public:
	};
	static_assert(sizeof(hknpRayCastQueryResult) == 0x60);
}
