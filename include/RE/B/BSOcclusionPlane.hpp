#pragma once

#include "RE/B/BSOcclusionShape.hpp"
#include "RE/N/NiFrustumPlanes.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class __declspec(novtable) BSOcclusionPlane
		: public BSOcclusionShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSOcclusionPlane };
		inline static constexpr auto VTABLE{ VTABLE::BSOcclusionPlane };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSOcclusionPlane };

		~BSOcclusionPlane() override; // 00

		enum class LINK : std::int32_t
		{
			kXNeg = 0,
			XPos = 1,
			kZNeg = 2,
			kZPos = 3
		};

		enum class LINKTYPE : std::int32_t
		{
			kNone = 0,
			kParent = 1,
			kChild = 2
		};

		// members
		NiPoint2 halfExtents;						   // 060
		NiFrustumPlanes cachedPlanes;				   // 068
		std::array<NiPoint3, 4> cachedVertices;		   // 0D8
		std::array<bool, 4> disabledPlanes;			   // 108
		bool twoSides;								   // 10C
		std::array<BSOcclusionPlane*, 4> linkedPlanes; // 110
	};
	static_assert(sizeof(BSOcclusionPlane) == 0x130);
}
