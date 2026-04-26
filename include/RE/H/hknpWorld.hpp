#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkBitField.hpp"
#include "RE/H/hkBlockStream.hpp"
#include "RE/H/hkIntSpaceUtil.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkSimdFloat32.hpp"
#include "RE/H/hkVector4f.hpp"
#include "RE/H/hknpBodyManager.hpp"
#include "RE/H/hknpConstraintManager.hpp"
#include "RE/H/hknpContactSolverType.hpp"
#include "RE/H/hknpMotionManager.hpp"
#include "RE/H/hknpShapeManager.hpp"
#include "RE/H/hknpSolverInfo.hpp"
#include "RE/H/hknpThreadSafetyCheck.hpp"
#include "RE/H/hknpWorldCinfo.hpp"
#include "RE/H/hknpWorldSignals.hpp"

namespace RE
{
	class hkBlockStreamAllocator;
	class hknpActionManager;
	class hknpBodyQualityLibrary;
	class hknpBroadPhase;
	class hknpCollisionCacheManager;
	class hknpCollisionDispatcher;
	class hknpCollisionQueryDispatcherBase;
	class hknpConstraintAtomSolver;
	class hknpContactConstraintSolver;
	class hknpDeactivationManager;
	class hknpEventDispatcher;
	class hknpInternalCommandProcessor;
	class hknpMaterialLibrary;
	class hknpModifierManager;
	class hknpMotionPropertiesLibrary;
	class hknpNullShapeTagCodec;
	class hknpPostCollideTask;
	class hknpPostSolveTask;
	class hknpShapeTagCodec;
	class hknpSimulation;
	class hknpSimulationContext;
	class hknpSolverSumVelocity;
	class hknpSolverVelocity;
	class hknpSpaceSplitter;
	class hkPrimaryCommandDispatcher;
	class hkSecondaryCommandDispatcher;

	class __declspec(novtable) hknpWorld
		: public hkReferencedObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpWorld };
		inline static constexpr auto VTABLE{ VTABLE::hknpWorld };

		enum class AdditionMode : std::int8_t
		{
			kDoNotAddBody = 0,
			kAddBodyNow = 1,
			kAddBodyInNextStep = 2
		};

		enum class SimulationStage : std::uint32_t
		{
			kNone = 0,
			kDone = 1 << 0,
			kPreCollide = 1 << 1,
			kCollide = 1 << 2,
			kPostCollide = 1 << 3,
			kPreSolve = 1 << 4,
			kSolve = 1 << 5,
			kPostSolve = 1 << 6
		};

		~hknpWorld() override; // 00

		// members
		hknpBodyManager bodyManager;																	 // 010
		hknpMotionManager motionManager;																 // 0D8
		hknpConstraintManager constraintManager;														 // 120
		hknpModifierManager* modifierManager;															 // 150
		hkRefPtr<hkBlockStreamAllocator> persistentStreamAllocator;										 // 158
		hkBlockStreamAllocator* stepLocalStreamAllocator;												 // 160
		hknpSimulation* simulation;																		 // 168
		hknpSpaceSplitter* spaceSplitter;																 // 170
		hknpBroadPhase* broadPhase;																		 // 178
		hkIntSpaceUtil intSpaceUtil;																	 // 180
		hkSimdFloat32 collisionTolerance;																 // 1E0
		hknpCollisionCacheManager* collisionCacheManager;												 // 1F0
		hknpCollisionDispatcher* collisionDispatcher;													 // 1F8
		hknpCollisionQueryDispatcherBase* collisionQueryDispatcher;										 // 200
		bool contactCachingEnabled;																		 // 208
		hkBlockStream<std::int8_t> lastFrameContactData;												 // 210
		REX::Enum<hknpContactSolverType::Enum, std::int32_t> contactSolverType;							 // 310
		hknpContactConstraintSolver* contactSolver;														 // 318
		hknpConstraintAtomSolver* constraintAtomSolver;													 // 320
		hknpSolverInfo solverInfo;																		 // 330
		bool enableSolverDynamicScheduling;																 // 470
		hkArray<hknpSolverVelocity> solverVelocities;													 // 478
		hkArray<hknpSolverSumVelocity> solverSumVelocities;												 // 488
		bool deactivationEnabled;																		 // 498
		hknpDeactivationManager* deactivationManager;													 // 4A0
		bool deleteCachesOnDeactivation;																 // 4A8
		hknpWorldSignals signals;																		 // 4B0
		hkPrimaryCommandDispatcher* commandDispatcher;													 // 598
		hkRefPtr<hkSecondaryCommandDispatcher> traceDispatcher;											 // 5A0
		std::uint16_t userData;																			 // 5A8
		hkVector4f gravity;																				 // 5B0
		hkRefPtr<hkReferencedObject> defaultModifierSet;												 // 5C0
		hkRefPtr<hknpMaterialLibrary> materialLibrary;													 // 5C8
		hkRefPtr<hknpMotionPropertiesLibrary> motionPropertiesLibrary;									 // 5D0
		hkRefPtr<hknpBodyQualityLibrary> qualityLibrary;												 // 5D8
		hkBitField dirtyMaterials;																		 // 5E0
		hkBitField dirtyQualities;																		 // 5F8
		hknpShapeManager shapeManager;																	 // 610
		hkRefPtr<hknpShapeTagCodec> shapeTagCodec;														 // 638
		hknpNullShapeTagCodec* nullShapeTagCodec;														 // 640
		hkRefPtr<hknpEventDispatcher> eventDispatcher;													 // 648
		hkRefPtr<hknpInternalCommandProcessor> internalPhysicsCommandDispatcher;						 // 650
		bool consistencyChecksEnabled;																	 // 658
		hknpPostCollideTask* postCollideTask;															 // 660
		hknpPostSolveTask* postSolveTask;																 // 668
		REX::EnumSet<SimulationStage, std::uint32_t> simulationStage;									 // 670
		hknpSimulationContext* simulationContext;														 // 678
		hknpActionManager* actionManager;																 // 680
		REX::EnumSet<hknpWorldCinfo::SimulationType, std::uint8_t> simulationType;						 // 688
		bool mergeEventsBeforeDispatch;																	 // 689
		REX::EnumSet<hknpWorldCinfo::LeavingBroadPhaseBehavior, std::uint8_t> leavingBroadPhaseBehavior; // 68A
		hknpThreadSafetyCheck threadSafetyCheck;														 // 690
	};
	static_assert(sizeof(hknpWorld) == 0x6D0);
}
