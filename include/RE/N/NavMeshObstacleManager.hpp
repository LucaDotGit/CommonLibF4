#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTaskJobber.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class bhkNPCollisionObject;
	class BSNavmeshObstacleData;
	class BSNavmeshReferenceObstacleArray;
	class ObstacleTaskData;

	class __declspec(novtable) NavMeshObstacleManager
		: public BSTSingletonSDM<NavMeshObstacleManager> // 00
	{
	public:
		enum class OBSTACLE_MANAGER_BACKGROUND_STATE : std::int32_t
		{
			kProcessingObstacles = 0,
			kWaitingForPathManagerPause = 1,
			kPauseRequested = 2,
			kPaused = 3
		};

		[[nodiscard]] static NavMeshObstacleManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<NavMeshObstacleManager**>{ ID::NavMeshObstacleManager::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] static BSReadWriteLock& GetUpdateLock()
		{
			static const auto UPDATE_LOCK = REL::Relocation<BSReadWriteLock*>{ ID::NavMeshObstacleManager::UpdateLock };
			return *UPDATE_LOCK;
		}

		// members
		bool updateAllObstacles;																				// 001
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> formIDMap;							// 008
		BSTArray<TESObjectREFR*> queuedRefsToAdd;																// 038
		BSTArray<TESObjectREFR*> queuedRefsToRemove;															// 050
		BSTArray<NiPointer<BSNavmeshObstacleData>> obstaclesUpdate;												// 068
		BSTArray<const bhkNPCollisionObject*> obstaclesToAddToUpdate;											// 080
		BSTArray<const bhkNPCollisionObject*> obstaclesToRemoveFromUpdate;										// 098
		BSTHashMap<const bhkNPCollisionObject*, NiPointer<BSNavmeshObstacleData>> collisionObjectToObstacleMap; // 0B0
		BSTSet<const bhkNPCollisionObject*> removeSignalSet;													// 0E0
		BSTSet<const bhkNPCollisionObject*> lostCollisionObjectSet;												// 110
		BSTArray<TESObjectREFR*> queuedClosedDoors;																// 140
		BSTArray<TESObjectREFR*> queuedOpenDoors;																// 158
		BSTArray<TESObjectREFR*> queuedRemovedDoors;															// 170
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> openDoorMap;							// 188
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> closedDoorMap;						// 1B0
		BSTaskJobber obstacleTaskletJobber;																		// 1D8
		BSTHashMap<TESFormID, ObstacleTaskData*> currentNavMeshTaskMap;											// 240
		BSTArray<ObstacleTaskData*> backgroundTasks;															// 270
		BSTArray<ObstacleTaskData*> processedTasks;																// 288
		mutable BSSpinLock processedTaskLock;																	// 2A0
		REX::Enum<OBSTACLE_MANAGER_BACKGROUND_STATE, std::int32_t> state;										// 2A8
		bool requestedPathManagerPause;																			// 2AC
		REX::Float32 timeToNextSwap;																			// 2B0
	};
	static_assert(sizeof(NavMeshObstacleManager) == 0x2B8);
}
