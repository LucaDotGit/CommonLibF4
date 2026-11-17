#pragma once

#include "RE/H/hknpQueryFilterData.hpp"

namespace RE
{
	class hknpCollisionFilter;

	class hknpCollisionQuery
	{
	public:
		// members
		hkPadSpu<hknpCollisionFilter*> filter; // 0x00
		hknpQueryFilterData filterData;		   // 0x08
		std::uint8_t levelOfDetail;			   // 0x18
	};

	static_assert(sizeof(hknpCollisionQuery) == 0x20);
}
