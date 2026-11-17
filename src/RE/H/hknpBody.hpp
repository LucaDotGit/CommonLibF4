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
			None = 0,
			ForceNarrowPhasePPU = 1 << 0
		};

		// members
		hkTransform transform;									// 0x00
		REX::EnumSet<hknpCollisionFlags, std::uint32_t> flags;	// 0x40
		std::uint32_t collisionFilterInfo;						// 0x44
		hknpShape* shape;										// 0x48
		hkAabb16 aabb;											// 0x50
		hknpBodyId id;											// 0x60
		hknpBodyId nextAttachedBodyId;							// 0x64
		hknpMotionId motionId;									// 0x68
		std::uint32_t broadPhaseId;								// 0x6C
		hknpMaterialId materialId;								// 0x70
		hknpBodyQualityId qualityId;							// 0x72
		std::uint8_t timAngle;									// 0x73
		std::uint16_t maxTimDistance;							// 0x74
		std::uint16_t maxContactDistance;						// 0x76
		std::uint32_t indexIntoActiveListOrDeactivatedIslandId; // 0x78
		hkHalf radiusOfComCenteredBoundingSphere;				// 0x7C
		REX::EnumSet<SpuFlagsEnum, std::uint8_t> spuFlags;		// 0x7E
		std::uint8_t shapeSizeDiv16;							// 0x7F
		std::array<std::uint16_t, 4> motionToBodyRotation;		// 0x80 - To-Do: `hkPackedUnitVector<4>`
		std::uintptr_t userData;								// 0x88
	};

	static_assert(sizeof(hknpBody) == 0x90);
}
