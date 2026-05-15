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
			kDoNothing = 0,
			kRemoveBody = 1,
			kFreezeBody = 2
		};

		enum class SimulationType : std::uint8_t
		{
			kSingleThreaded = 0,
			kMultiThreaded = 2
		};

		// members
		std::int32_t bodyBufferCapacity;												 // 00
		hknpBody* userBodyBuffer;														 // 08
		std::int32_t motionBufferCapacity;												 // 10
		hknpMotion* userMotionBuffer;													 // 18
		std::int32_t constraintBufferCapacity;											 // 20
		hknpConstraint* userConstraintBuffer;											 // 28
		hkBlockStreamAllocator* persistentStreamAllocator;								 // 30
		hkRefPtr<hknpMaterialLibrary> materialLibrary;									 // 38
		hkRefPtr<hknpMotionPropertiesLibrary> motionPropertiesLibrary;					 // 40
		hkRefPtr<hknpBodyQualityLibrary> qualityLibrary;								 // 48
		REX::EnumSet<SimulationType, std::uint8_t> simulationType;						 // 50
		std::int32_t numSplitterCells;													 // 54
		hkVector4 gravity;																 // 60
		bool enableContactCaching;														 // 70
		bool mergeEventsBeforeDispatch;													 // 71
		REX::EnumSet<LeavingBroadPhaseBehavior, std::uint8_t> leavingBroadPhaseBehavior; // 72
		hkAabb broadPhaseAabb;															 // 80
		hkRefPtr<hknpBroadPhaseConfig> broadPhaseConfig;								 // A0
		hkRefPtr<hknpCollisionFilter> collisionFilter;									 // A8
		hkRefPtr<hknpShapeTagCodec> shapeTagCodec;										 // B0
		REX::Float32 collisionTolerance;												 // B8
		REX::Float32 relativeCollisionAccuracy;											 // BC
		bool enableWeldingForDefaultObjects;											 // C0
		bool enableWeldingForCriticalObjects;											 // C1
		REX::Float32 solverTau;															 // C4
		REX::Float32 solverDamp;														 // C8
		std::int32_t solverIterations;													 // CC
		std::int32_t solverMicrosteps;													 // D0
		REX::Float32 defaultSolverTimestep;												 // D4
		REX::Float32 maxApproachSpeedForHighQualitySolver;								 // D8
		bool enableDeactivation;														 // DC
		bool deleteCachesOnDeactivation;												 // DD
		std::int32_t largeIslandSize;													 // E0
		bool enableSolverDynamicScheduling;												 // E4
		REX::EnumSet<hknpContactSolverType::Enum> contactSolverType;					 // E8
		REX::Float32 unitScale;															 // EC
		bool applyUnitScaleToStaticConstants;											 // F0
	};
	static_assert(sizeof(hknpWorldCinfo) == 0x100);
}
