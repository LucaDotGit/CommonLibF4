#pragma once

#include "RE/B/BSOcclusionShape.hpp"
#include "RE/N/NiFrustumPlanes.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSMultiBoundShape;

	class __declspec(novtable) BSOcclusionBox : public BSOcclusionShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSOcclusionBox;
		inline static constexpr const auto& VTABLE = VTABLE::BSOcclusionBox;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSOcclusionBox;

		~BSOcclusionBox() override; // 0x00

		// members
		NiPoint3A halfExtents;							 // 0x060
		std::array<NiFrustumPlanes, 2> cachedPlanes;	 // 0x070
		std::array<NiPoint3A, 8> cacvesVertices;		 // 0x150
		BSMultiBoundShape* mbShape;						 // 0x1D0
		std::array<bool, 12> disablesPlanes;			 // 0x1D8
		std::array<std::int32_t, 6> secondaryFacePlanes; // 0x1E4
		std::array<std::uint32_t, 8> hullIndex;			 // 0x1FC
		std::uint32_t hullLength;						 // 0x21C
	};

	static_assert(sizeof(BSOcclusionBox) == 0x220);
}
