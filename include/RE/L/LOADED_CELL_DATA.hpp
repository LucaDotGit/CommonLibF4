#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSpinLock.hpp"
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
			ObjectRefHandle handle;		// 00
			std::int32_t numSkipFrames; // 04
		};
		static_assert(sizeof(AnimatedRefObject) == 0x08);

		// members
		BSTHashMap<ObjectRefHandle, TESForm*> emittanceSourceRefMap;			   // 000
		BSTHashMap<ObjectRefHandle, NiNode*> emittanceLightRefMap;				   // 030
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>> multiboundRefMap; // 060
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle> refMultiboundMap;		   // 090
		BSTArray<NiPointer<NiNode>> preCombined;								   // 0C0
		BSTArray<NiPointer<NiNode>> attachedTransitionCells;					   // 0D8
		BSTArray<AnimatedRefObject> animatedRefs;								   // 0F0
		BSTArray<ObjectRefHandle> flickeringLights;								   // 108
		BSTArray<ObjectRefHandle> movingRefs;									   // 120
		BSTArray<ObjectRefHandle> decalRefs;									   // 138
		BSTArray<ObjectRefHandle> skyActors;									   // 150
		BSTArray<ObjectRefHandle> flightAvoidAreas;								   // 168
		mutable BSReadWriteLock waterLock;										   // 180
		void* combinedGeometry;													   // 188 - TODO: `BSResource::RHandleType<BSResource::Entry<BGSCombinedCellGeometryDB::Data*, BSResource::EntryDBTraits<BGSCombinedCellGeometryDB::DBTraits, BSResource::EntryDB<BGSCombinedCellGeometryDB::DBTraits>>::CArgs>, BSResource::EntryDB<BGSCombinedCellGeometryDB::DBTraits>>`
		NiPointer<QueuedFile> combinedGeometryTask;								   // 190
		BSSimpleList<ObjectRefHandle> activatingRefs;							   // 198
		BSSimpleList<ObjectRefHandle> waterRefs;								   // 1A8
		NiPointer<BSPortalGraph> portalGraph;									   // 1B8
		NiPointer<NiNode> cell3D;												   // 1C0
		NiPointer<NiNode> lightMarkerNode;										   // 1C8
		NiPointer<NiNode> soundMarkerNode;										   // 1D0
		NiPointer<NiNode> multiBoundNode;										   // 1D8
		NiPointer<NiNode> combinedObjects;										   // 1E0
		NiPointer<NiNode> combinedStaticCollision;								   // 1E8
		BGSEncounterZone* encounterZone;										   // 1F0
		std::uint64_t visibleDistantFadeInTime;									   // 1F8
		std::int32_t criticalQueuedRefCount;									   // 200
		std::int32_t queuedRefCount;											   // 204
		std::int32_t queuedDistantRefCount;										   // 208
		std::uint32_t refsAttachedDelay;										   // 20C
		BSTAtomicValue<std::uint32_t> combinedObjectsAttached;					   // 210
		bool decalsQueued;														   // 214
		bool refsFullyLoaded;													   // 215
		bool combinedObjectsRegistered;											   // 216
		bool grassIsShown;														   // 217
	};
	static_assert(sizeof(LOADED_CELL_DATA) == 0x218);
}
