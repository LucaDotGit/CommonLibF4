#pragma once

#include "RE/H/hkcdRay.hpp"
#include "RE/H/hkcdRayQueryFlags.hpp"
#include "RE/H/hknpCollisionQuery.hpp"

namespace RE
{
	class hknpRayCastQuery
		: public hknpCollisionQuery // 00
	{
	public:
		// members
		hkcdRay ray;												// 20
		REX::EnumSet<hkcdRayQueryFlags::Enum, std::uint32_t> flags; // 50
	};
	static_assert(sizeof(hknpRayCastQuery) == 0x60);
}
