#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BGSTerrainNode;
	class NiCamera;

	class BGSTerrainManager
	{
	public:
		class CullState
		{
		public:
			// members
			bool cullRoot;		// 0x00
			bool cullLand;		// 0x01
			bool cullTrees;		// 0x02
			bool cullObjects;	// 0x03
			bool cullInstanced; // 0x04
		};

		static_assert(sizeof(CullState) == 0x05);

		class QuickCullDAta
		{
		public:
			// members
			NiPoint2 frustNearLeft;	 // 0x00
			NiPoint2 frustFarLeft;	 // 0x08
			NiPoint2 frustNearRight; // 0x10
			NiPoint2 frustFarRight;	 // 0x18
		};

		static_assert(sizeof(QuickCullDAta) == 0x20);

		void RecomputeQuickCullData(const NiCamera* a_camera)
		{
			using FuncType = decltype(&BGSTerrainManager::RecomputeQuickCullData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSTerrainManager::RecomputeQuickCullData);
			std::invoke(FUNC, this, a_camera);
		}

		// members
		bool mapMode;								// 0x000
		TESWorldSpace* world;						// 0x008
		BGSTerrainNode* rootNode;					// 0x010
		std::int16_t minCellX;						// 0x018
		std::int16_t minCellY;						// 0x01A
		std::uint32_t maxLevel;						// 0x01C
		std::uint32_t minLevel;						// 0x020
		std::uint32_t rootLevel;					// 0x024
		std::uint32_t segmentedBlockLevel;			// 0x028
		std::uint32_t treeLevel;					// 0x02C
		CullState savedCullState;					// 0x030
		CullState activeCullState;					// 0x035
		bool cullActive;							// 0x03A
		bool needsImmediateUpdate;					// 0x03B
		bool initialUpdateDone;						// 0x03C
		bool hasLOD;								// 0x03D
		QuickCullDAta cullData;						// 0x040
		bool staticDataLoaded;						// 0x060
		BSTArray<BGSTerrainNode*> updateUpdates;	// 0x068
		std::uint32_t nextUpdateNode;				// 0x080
		BSTArray<BGSTerrainNode*> immediateUpdates; // 0x088
		mutable BSSpinLock immediateUpdateLock;		// 0x0A0
		bool lockedLOD;								// 0x0A8
		std::uint32_t lockedTerrainLOD;				// 0x0AC
		std::uint32_t lockedObjectLOD;				// 0x0B0
		std::uint32_t totalChildNodes;				// 0x0B4
		std::uint8_t* childNodeBufferStart;			// 0x0B8
		std::uint8_t* childNodeBufferCurr;			// 0x0C0
		std::uint8_t* childNodeBufferEnd;			// 0x0C8
		std::uint32_t nodeCount;					// 0x0D0
		std::uint32_t loadedRectUpdateDelay;		// 0x0D4
		NiPoint3 interiorAdjustedOffset;			// 0x0D8
		BSTArray<BGSTerrainNode*> fadeNodeA;		// 0x0E8
	};

	static_assert(sizeof(BGSTerrainManager) == 0x100);
}
