#pragma once

#include "RE/H/hkPadSpu.hpp"
#include "RE/H/hknpMaterialId.hpp"

namespace RE
{
	class hknpQueryFilterData
	{
	public:
		// members
		hknpMaterialId materialId;					 // 0x00
		hkPadSpu<std::uint32_t> collisionFilterInfo; // 0x04
		hkPadSpu<std::uint64_t> userData;			 // 0x08
	};

	static_assert(sizeof(hknpQueryFilterData) == 0x10);
}
