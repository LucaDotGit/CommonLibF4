#pragma once

#include "RE/H/hkArray.hpp"
#include "RE/H/hkBitField.hpp"
#include "RE/H/hkBlockStream.hpp"
#include "RE/H/hkIntSpaceUtil.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hkReferencedObject.hpp"
#include "RE/H/hkSimdFloat32.hpp"
#include "RE/H/hkVector4.hpp"
#include "RE/H/hkcdRayQueryFlags.hpp"
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
	enum class hknpCollisionFlags : std::uint32_t;

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

	class __declspec(novtable) hknpWorld : public hkReferencedObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpWorld;
		inline static constexpr const auto& VTABLE = VTABLE::hknpWorld;

		enum class AdditionMode : std::int8_t
		{
			DoNotAddBody = 0,
			AddBodyNow = 1,
			AddBodyInNextStep = 2
		};

		enum class RebuildCachesMode : std::int8_t
		{
			Rebuild = 0,
			Keep = 1
		};

		enum class SimulationStage : std::uint32_t
		{
			None = 0,
			Done = 1 << 0,
			PreCollide = 1 << 1,
			Collide = 1 << 2,
			PostCollide = 1 << 3,
			PreSolve = 1 << 4,
			Solve = 1 << 5,
			PostSolve = 1 << 6
		};

		~hknpWorld() override; // 0x00

		void AddBodies(
			hknpBodyId* a_ids,
			std::uint32_t a_idCount,
			AdditionMode a_additionMode,
			hkcdRayQueryFlags::Enum a_additionFlags)
		{
			using FuncType = decltype(&hknpWorld::AddBodies);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::AddBodies);
			std::invoke(FUNC, this, a_ids, a_idCount, a_additionMode, a_additionFlags);
		}

		[[nodiscard]]
		auto CreateBody(
			const hknpBodyCinfo& a_cInfo,
			AdditionMode a_additionMode = AdditionMode::AddBodyNow,
			hkcdRayQueryFlags::Enum a_additionFlags = hkcdRayQueryFlags::Enum::None) -> hknpBodyId&
		{
			using FuncType =
				hknpBodyId&(hknpWorld*, hknpBodyId&, const hknpBodyCinfo&, AdditionMode, hkcdRayQueryFlags::Enum);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::CreateBody);

			auto bodyId = hknpBodyId();
			return std::invoke(FUNC, this, bodyId, a_cInfo, a_additionMode, a_additionFlags);
		}

		[[nodiscard]]
		auto CreateMotion(const hknpMotionCinfo& a_cInfo) -> hknpMotionId&
		{
			using FuncType = hknpMotionId&(hknpWorld*, hknpMotionId&, const hknpMotionCinfo&);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::CreateMotion);

			auto motionId = hknpMotionId();
			return std::invoke(FUNC, this, motionId, a_cInfo);
		}

		void DisableBodyFlags(
			hknpBodyId a_bodyId,
			hknpCollisionFlags a_enabledFlags,
			RebuildCachesMode a_cacheBehavior = RebuildCachesMode::Rebuild)
		{
			using FuncType = decltype(&hknpWorld::DisableBodyFlags);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::DisableBodyFlags);
			std::invoke(FUNC, this, a_bodyId, a_enabledFlags, a_cacheBehavior);
		}

		void EnableBodyFlags(
			hknpBodyId a_bodyId,
			hknpCollisionFlags a_enabledFlags,
			RebuildCachesMode a_cacheBehavior = RebuildCachesMode::Rebuild)
		{
			using FuncType = decltype(&hknpWorld::EnableBodyFlags);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::EnableBodyFlags);
			std::invoke(FUNC, this, a_bodyId, a_enabledFlags, a_cacheBehavior);
		}

		[[nodiscard]]
		auto GetActionManager() -> hknpActionManager*
		{
			using FuncType = decltype(&hknpWorld::GetActionManager);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::GetActionManager);
			return std::invoke(FUNC, this);
		}

		void SetBodyCollisionFilterInfo(
			hknpBodyId a_bodyId,
			std::uint32_t a_collisionFilterInfo,
			RebuildCachesMode a_cacheBehavior = RebuildCachesMode::Rebuild)
		{
			using FuncType = decltype(&hknpWorld::SetBodyCollisionFilterInfo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::SetBodyCollisionFilterInfo);
			std::invoke(FUNC, this, a_bodyId, a_collisionFilterInfo, a_cacheBehavior);
		}

		void SetBodyMotion(
			hknpBodyId a_bodyId,
			hknpMotionId a_motionId,
			RebuildCachesMode a_cacheBehavior = RebuildCachesMode::Rebuild)
		{
			using FuncType = decltype(&hknpWorld::SetBodyMotion);
			static const auto FUNC = REL::Relocation<FuncType>(ID::hknpWorld::SetBodyMotion);
			std::invoke(FUNC, this, a_bodyId, a_motionId, a_cacheBehavior);
		}

		// members
		hknpBodyManager bodyManager;																	 // 0x010
		hknpMotionManager motionManager;																 // 0x0D8
		hknpConstraintManager constraintManager;														 // 0x120
		hknpModifierManager* modifierManager;															 // 0x150
		hkRefPtr<hkBlockStreamAllocator> persistentStreamAllocator;										 // 0x158
		hkBlockStreamAllocator* stepLocalStreamAllocator;												 // 0x160
		hknpSimulation* simulation;																		 // 0x168
		hknpSpaceSplitter* spaceSplitter;																 // 0x170
		hknpBroadPhase* broadPhase;																		 // 0x178
		hkIntSpaceUtil intSpaceUtil;																	 // 0x180
		hkSimdFloat32 collisionTolerance;																 // 0x1E0
		hknpCollisionCacheManager* collisionCacheManager;												 // 0x1F0
		hknpCollisionDispatcher* collisionDispatcher;													 // 0x1F8
		hknpCollisionQueryDispatcherBase* collisionQueryDispatcher;										 // 0x200
		bool contactCachingEnabled;																		 // 0x208
		hkBlockStream<std::int8_t> lastFrameContactData;												 // 0x210
		REX::Enum<hknpContactSolverType::Enum, std::int32_t> contactSolverType;							 // 0x310
		hknpContactConstraintSolver* contactSolver;														 // 0x318
		hknpConstraintAtomSolver* constraintAtomSolver;													 // 0x320
		hknpSolverInfo solverInfo;																		 // 0x330
		bool enableSolverDynamicScheduling;																 // 0x470
		hkArray<hknpSolverVelocity> solverVelocities;													 // 0x478
		hkArray<hknpSolverSumVelocity> solverSumVelocities;												 // 0x488
		bool deactivationEnabled;																		 // 0x498
		hknpDeactivationManager* deactivationManager;													 // 0x4A0
		bool deleteCachesOnDeactivation;																 // 0x4A8
		hknpWorldSignals signals;																		 // 0x4B0
		hkPrimaryCommandDispatcher* commandDispatcher;													 // 0x598
		hkRefPtr<hkSecondaryCommandDispatcher> traceDispatcher;											 // 0x5A0
		std::uintptr_t userData;																		 // 0x5A8
		hkVector4 gravity;																				 // 0x5B0
		hkRefPtr<hkReferencedObject> defaultModifierSet;												 // 0x5C0
		hkRefPtr<hknpMaterialLibrary> materialLibrary;													 // 0x5C8
		hkRefPtr<hknpMotionPropertiesLibrary> motionPropertiesLibrary;									 // 0x5D0
		hkRefPtr<hknpBodyQualityLibrary> qualityLibrary;												 // 0x5D8
		hkBitField dirtyMaterials;																		 // 0x5E0
		hkBitField dirtyQualities;																		 // 0x5F8
		hknpShapeManager shapeManager;																	 // 0x610
		hkRefPtr<hknpShapeTagCodec> shapeTagCodec;														 // 0x638
		hknpNullShapeTagCodec* nullShapeTagCodec;														 // 0x640
		hkRefPtr<hknpEventDispatcher> eventDispatcher;													 // 0x648
		hkRefPtr<hknpInternalCommandProcessor> internalPhysicsCommandDispatcher;						 // 0x650
		bool consistencyChecksEnabled;																	 // 0x658
		hknpPostCollideTask* postCollideTask;															 // 0x660
		hknpPostSolveTask* postSolveTask;																 // 0x668
		REX::EnumSet<SimulationStage, std::uint32_t> simulationStage;									 // 0x670
		hknpSimulationContext* simulationContext;														 // 0x678
		hknpActionManager* actionManager;																 // 0x680
		REX::EnumSet<hknpWorldCinfo::SimulationType, std::uint8_t> simulationType;						 // 0x688
		bool mergeEventsBeforeDispatch;																	 // 0x689
		REX::EnumSet<hknpWorldCinfo::LeavingBroadPhaseBehavior, std::uint8_t> leavingBroadPhaseBehavior; // 0x68A
		hknpThreadSafetyCheck threadSafetyCheck;														 // 0x690
	};

	static_assert(sizeof(hknpWorld) == 0x6D0);
}
