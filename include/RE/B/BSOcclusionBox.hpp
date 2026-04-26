#pragma once

#include "RE/B/BSOcclusionShape.hpp"
#include "RE/N/NiFrustumPlanes.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSMultiBoundShape;

	class __declspec(novtable) BSOcclusionBox
		: public BSOcclusionShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSOcclusionBox };
		inline static constexpr auto VTABLE{ VTABLE::BSOcclusionBox };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSOcclusionBox };

		~BSOcclusionBox() override; // 00

		// members
		NiPoint3A halfExtents;							 // 060
		std::array<NiFrustumPlanes, 2> cachedPlanes;	 // 070
		std::array<NiPoint3A, 8> cacvesVertices;		 // 150
		BSMultiBoundShape* mbShape;						 // 1D0
		std::array<bool, 12> disablesPlanes;			 // 1D8
		std::array<std::int32_t, 6> secondaryFacePlanes; // 1E4
		std::array<std::uint32_t, 8> hullIndex;			 // 1FC
		std::uint32_t hullLength;						 // 21C
	};
	static_assert(sizeof(BSOcclusionBox) == 0x220);
}
