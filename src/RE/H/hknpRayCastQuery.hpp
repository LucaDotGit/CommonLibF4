#pragma once

#include "RE/H/hkcdRay.hpp"
#include "RE/H/hkcdRayQueryFlags.hpp"
#include "RE/H/hknpCollisionQuery.hpp"

namespace RE
{
	class hknpRayCastQuery : public hknpCollisionQuery // 0x00
	{
	public:
		// members
		hkcdRay ray;												// 0x20
		REX::EnumSet<hkcdRayQueryFlags::Enum, std::uint32_t> flags; // 0x50
	};

	static_assert(sizeof(hknpRayCastQuery) == 0x60);
}
