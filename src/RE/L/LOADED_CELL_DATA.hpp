#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class AnimatedRefObject;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class NiNode;
	class QueuedFile;

	class LOADED_CELL_DATA
	{
	public:
		class AnimatedRefObject
		{
		public:
			// members
			ObjectRefHandle handle;		// 0x00
			std::int32_t numSkipFrames; // 0x04
		};

		static_assert(sizeof(AnimatedRefObject) == 0x08);

		// members
		BSTHashMap<ObjectRefHandle, TESForm*> emittanceSourceRefMap;			   // 0x000
		BSTHashMap<ObjectRefHandle, NiNode*> emittanceLightRefMap;				   // 0x030
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap; // 0x060
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle> refMultiboundMap;		   // 0x090
		BSTArray<NiPointer<NiNode>> preCombined;								   // 0x0C0
		BSTArray<NiPointer<NiNode>> attachedTransitionCells;					   // 0x0D8
		BSTArray<AnimatedRefObject> animatedRefs;								   // 0x0F0
		BSTArray<ObjectRefHandle> flickeringLights;								   // 0x108
		BSTArray<ObjectRefHandle> movingRefs;									   // 0x120
		BSTArray<ObjectRefHandle> decalRefs;									   // 0x138
		BSTArray<ObjectRefHandle> skyActors;									   // 0x150
		BSTArray<ObjectRefHandle> flightAvoidAreas;								   // 0x168
		mutable BSReadWriteLock waterLock;										   // 0x180
		void* combinedGeometry;													   // 0x188 - To-Do:
								// `BSResource::RHandleType<BSResource::Entry<BGSCombinedCellGeometryDB::Data*,
								// BSResource::EntryDBTraits<BGSCombinedCellGeometryDB::DBTraits,
								// BSResource::EntryDB<BGSCombinedCellGeometryDB::DBTraits>>::CArgs>,
								// BSResource::EntryDB<BGSCombinedCellGeometryDB::DBTraits>>`
		NiPointer<QueuedFile> combinedGeometryTask;			   // 0x190
		BSSimpleList<ObjectRefHandle> activatingRefs;		   // 0x198
		BSSimpleList<ObjectRefHandle> waterRefs;			   // 0x1A8
		NiPointer<BSPortalGraph> portalGraph;				   // 0x1B8
		NiPointer<NiNode> cell3D;							   // 0x1C0
		NiPointer<NiNode> lightMarkerNode;					   // 0x1C8
		NiPointer<NiNode> soundMarkerNode;					   // 0x1D0
		NiPointer<NiNode> multiBoundNode;					   // 0x1D8
		NiPointer<NiNode> combinedObjects;					   // 0x1E0
		NiPointer<NiNode> combinedStaticCollision;			   // 0x1E8
		BGSEncounterZone* encounterZone;					   // 0x1F0
		std::uint64_t visibleDistantFadeInTime;				   // 0x1F8
		std::int32_t criticalQueuedRefCount;				   // 0x200
		std::int32_t queuedRefCount;						   // 0x204
		std::int32_t queuedDistantRefCount;					   // 0x208
		std::uint32_t refsAttachedDelay;					   // 0x20C
		BSTAtomicValue<std::uint32_t> combinedObjectsAttached; // 0x210
		bool decalsQueued;									   // 0x214
		bool refsFullyLoaded;								   // 0x215
		bool combinedObjectsRegistered;						   // 0x216
		bool grassIsShown;									   // 0x217
	};

	static_assert(sizeof(LOADED_CELL_DATA) == 0x218);
}
