#pragma once

#include "RE/B/BSOcclusionShape.hpp"
#include "RE/N/NiFrustumPlanes.hpp"
#include "RE/N/NiPoint2.hpp"

namespace RE
{
	class __declspec(novtable) BSOcclusionPlane : public BSOcclusionShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSOcclusionPlane;
		inline static constexpr const auto& VTABLE = VTABLE::BSOcclusionPlane;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSOcclusionPlane;

		~BSOcclusionPlane() override; // 0x00

		enum class LINK : std::int32_t
		{
			XNeg = 0,
			XPos = 1,
			ZNeg = 2,
			ZPos = 3
		};

		enum class LINKTYPE : std::int32_t
		{
			None = 0,
			Parent = 1,
			Child = 2
		};

		// members
		NiPoint2 halfExtents;						   // 0x060
		NiFrustumPlanes cachedPlanes;				   // 0x068
		std::array<NiPoint3, 4> cachedVertices;		   // 0x0D8
		std::array<bool, 4> disabledPlanes;			   // 0x108
		bool twoSides;								   // 0x10C
		std::array<BSOcclusionPlane*, 4> linkedPlanes; // 0x110
	};

	static_assert(sizeof(BSOcclusionPlane) == 0x130);
}
