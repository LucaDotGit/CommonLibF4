#pragma once

#include "RE/H/hkAabb16.hpp"
#include "RE/H/hkHalf.hpp"
#include "RE/H/hkTransform.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/H/hknpBodyQualityId.hpp"
#include "RE/H/hknpCollisionFlags.hpp"
#include "RE/H/hknpMaterialId.hpp"
#include "RE/H/hknpMotionId.hpp"

namespace RE
{
	class hknpShape;

	class hknpBody
	{
	public:
		enum class SpuFlagsEnum : std::uint8_t
		{
			kNone = 0,
			kForceNarrowPhasePPU = 1 << 0
		};

		// members
		hkTransform transform;									// 00
		REX::EnumSet<hknpCollisionFlags, std::uint32_t> flags;	// 40
		std::uint32_t collisionFilterInfo;						// 44
		hknpShape* shape;										// 48
		hkAabb16 aabb;											// 50
		hknpBodyId id;											// 60
		hknpBodyId nextAttachedBodyId;							// 64
		hknpMotionId motionId;									// 68
		std::uint32_t broadPhaseId;								// 6C
		hknpMaterialId materialId;								// 70
		hknpBodyQualityId qualityId;							// 72
		std::uint8_t timAngle;									// 73
		std::uint16_t maxTimDistance;							// 74
		std::uint16_t maxContactDistance;						// 76
		std::uint32_t indexIntoActiveListOrDeactivatedIslandId; // 78
		hkHalf radiusOfComCenteredBoundingSphere;				// 7C
		REX::EnumSet<SpuFlagsEnum, std::uint8_t> spuFlags;		// 7E
		std::uint8_t shapeSizeDiv16;							// 7F
		std::array<std::uint16_t, 4> motionToBodyRotation;		// 80 - TODO: `hkPackedUnitVector<4>`
		std::uintptr_t userData;								// 88
	};
	static_assert(sizeof(hknpBody) == 0x90);
}
