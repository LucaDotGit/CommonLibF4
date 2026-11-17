#pragma once

#include "RE/H/hkAabb.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpContactSolverType.hpp"

namespace RE
{
	class hkBlockStreamAllocator;
	class hknpBody;
	class hknpBodyQualityLibrary;
	class hknpBroadPhaseConfig;
	class hknpCollisionFilter;
	class hknpConstraint;
	class hknpMaterialLibrary;
	class hknpMotion;
	class hknpMotionPropertiesLibrary;
	class hknpShapeTagCodec;

	class hknpWorldCinfo
	{
	public:
		enum class LeavingBroadPhaseBehavior : std::uint8_t
		{
			DoNothing = 0,
			RemoveBody = 1,
			FreezeBody = 2
		};

		enum class SimulationType : std::uint8_t
		{
			SingleThreaded = 0,
			MultiThreaded = 2
		};

		// members
		std::int32_t bodyBufferCapacity;												 // 0x00
		hknpBody* userBodyBuffer;														 // 0x08
		std::int32_t motionBufferCapacity;												 // 0x10
		hknpMotion* userMotionBuffer;													 // 0x18
		std::int32_t constraintBufferCapacity;											 // 0x20
		hknpConstraint* userConstraintBuffer;											 // 0x28
		hkBlockStreamAllocator* persistentStreamAllocator;								 // 0x30
		hkRefPtr<hknpMaterialLibrary> materialLibrary;									 // 0x38
		hkRefPtr<hknpMotionPropertiesLibrary> motionPropertiesLibrary;					 // 0x40
		hkRefPtr<hknpBodyQualityLibrary> qualityLibrary;								 // 0x48
		REX::EnumSet<SimulationType, std::uint8_t> simulationType;						 // 0x50
		std::int32_t numSplitterCells;													 // 0x54
		hkVector4 gravity;																 // 0x60
		bool enableContactCaching;														 // 0x70
		bool mergeEventsBeforeDispatch;													 // 0x71
		REX::EnumSet<LeavingBroadPhaseBehavior, std::uint8_t> leavingBroadPhaseBehavior; // 0x72
		hkAabb broadPhaseAabb;															 // 0x80
		hkRefPtr<hknpBroadPhaseConfig> broadPhaseConfig;								 // 0xA0
		hkRefPtr<hknpCollisionFilter> collisionFilter;									 // 0xA8
		hkRefPtr<hknpShapeTagCodec> shapeTagCodec;										 // 0xB0
		REX::Float32 collisionTolerance;												 // 0xB8
		REX::Float32 relativeCollisionAccuracy;											 // 0xBC
		bool enableWeldingForDefaultObjects;											 // 0xC0
		bool enableWeldingForCriticalObjects;											 // 0xC1
		REX::Float32 solverTau;															 // 0xC4
		REX::Float32 solverDamp;														 // 0xC8
		std::int32_t solverIterations;													 // 0xCC
		std::int32_t solverMicrosteps;													 // 0xD0
		REX::Float32 defaultSolverTimestep;												 // 0xD4
		REX::Float32 maxApproachSpeedForHighQualitySolver;								 // 0xD8
		bool enableDeactivation;														 // 0xDC
		bool deleteCachesOnDeactivation;												 // 0xDD
		std::int32_t largeIslandSize;													 // 0xE0
		bool enableSolverDynamicScheduling;												 // 0xE4
		REX::EnumSet<hknpContactSolverType::Enum> contactSolverType;					 // 0xE8
		REX::Float32 unitScale;															 // 0xEC
		bool applyUnitScaleToStaticConstants;											 // 0xF0
	};

	static_assert(sizeof(hknpWorldCinfo) == 0x100);
}
