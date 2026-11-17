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
	class BSReadWriteLock;
	class ObstacleTaskData;

	class __declspec(novtable) NavMeshObstacleManager : public BSTSingletonSDM<NavMeshObstacleManager> // 0x00
	{
	public:
		enum class OBSTACLE_MANAGER_BACKGROUND_STATE : std::int32_t
		{
			ProcessingObstacles = 0,
			WaitingForPathManagerPause = 1,
			PauseRequested = 2,
			Paused = 3
		};

		[[nodiscard]]
		static auto GetSingleton() noexcept -> NavMeshObstacleManager*
		{
			static const auto SINGLETON =
				REL::Relocation<NavMeshObstacleManager**>{ID::NavMeshObstacleManager::Singleton};
			return *SINGLETON;
		}

		[[nodiscard]]
		static auto GetUpdateLock() noexcept -> BSReadWriteLock&
		{
			static const auto UPDATE_LOCK = REL::Relocation<BSReadWriteLock*>(ID::NavMeshObstacleManager::UpdateLock);
			return *UPDATE_LOCK;
		}

		// members
		bool updateAllObstacles;																				// 0x001
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> formIDMap;							// 0x008
		BSTArray<TESObjectREFR*> queuedRefsToAdd;																// 0x038
		BSTArray<TESObjectREFR*> queuedRefsToRemove;															// 0x050
		BSTArray<NiPointer<BSNavmeshObstacleData>> obstaclesUpdate;												// 0x068
		BSTArray<const bhkNPCollisionObject*> obstaclesToAddToUpdate;											// 0x080
		BSTArray<const bhkNPCollisionObject*> obstaclesToRemoveFromUpdate;										// 0x098
		BSTHashMap<const bhkNPCollisionObject*, NiPointer<BSNavmeshObstacleData>> collisionObjectToObstacleMap; // 0x0B0
		BSTSet<const bhkNPCollisionObject*> removeSignalSet;													// 0x0E0
		BSTSet<const bhkNPCollisionObject*> lostCollisionObjectSet;												// 0x110
		BSTArray<TESObjectREFR*> queuedClosedDoors;																// 0x140
		BSTArray<TESObjectREFR*> queuedOpenDoors;																// 0x158
		BSTArray<TESObjectREFR*> queuedRemovedDoors;															// 0x170
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> openDoorMap;							// 0x188
		BSTHashMap<TESFormID, NiPointer<BSNavmeshReferenceObstacleArray>> closedDoorMap;						// 0x1B0
		BSTaskJobber obstacleTaskletJobber;																		// 0x1D8
		BSTHashMap<TESFormID, ObstacleTaskData*> currentNavMeshTaskMap;											// 0x240
		BSTArray<ObstacleTaskData*> backgroundTasks;															// 0x270
		BSTArray<ObstacleTaskData*> processedTasks;																// 0x288
		mutable BSSpinLock processedTaskLock;																	// 0x2A0
		REX::Enum<OBSTACLE_MANAGER_BACKGROUND_STATE, std::int32_t> state;										// 0x2A8
		bool requestedPathManagerPause;																			// 0x2AC
		REX::Float32 timeToNextSwap;																			// 0x2B0
	};

	static_assert(sizeof(NavMeshObstacleManager) == 0x2B8);
}
