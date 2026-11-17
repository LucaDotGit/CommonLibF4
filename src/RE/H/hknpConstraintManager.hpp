#pragma once

#include "RE/H/hkHandle.hpp"
#include "RE/H/hknpConstraintIdDiscriminant.hpp"

namespace RE
{
	class hknpConstraint;
	class hknpWorld;

	class hknpConstraintManager
	{
	public:
		// members
		hknpWorld* world;				  // 0x00
		hknpConstraint* constraintBuffer; // 0x08
		std::uint32_t capacity;			  // 0x10
		bool constraintBufferIsUserOwned; // 0x14
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant>
			firstDestroyedConstraintId; // 0x18
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant>
			firstFreeConstraintId;			   // 0x1C
		std::uint32_t numAllocatedConstraints; // 0x20
		std::uint32_t numDestroyedConstraints; // 0x24
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant>
			peakConstraintId; // 0x28
	};

	static_assert(sizeof(hknpConstraintManager) == 0x30);
}
