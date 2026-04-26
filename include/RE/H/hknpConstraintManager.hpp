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
		hknpWorld* world;																											// 00
		hknpConstraint* constraintBuffer;																							// 08
		std::uint32_t capacity;																										// 10
		bool constraintBufferIsUserOwned;																							// 14
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant> firstDestroyedConstraintId; // 18
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant> firstFreeConstraintId;		// 1C
		std::uint32_t numAllocatedConstraints;																						// 20
		std::uint32_t numDestroyedConstraints;																						// 24
		hkHandle<std::uint32_t, std::numeric_limits<std::int32_t>::max(), hknpConstraintIdDiscriminant> peakConstraintId;			// 28
	};
	static_assert(sizeof(hknpConstraintManager) == 0x30);
}
