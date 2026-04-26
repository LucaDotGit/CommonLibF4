#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class GridCellArray;
	class GridDistantArray;
	class ImageSpaceModifierInstance;
	class LoadedAreaBound;
	class NavMeshInfoMap;
	class NiAVObject;
	class NiDirectionalLight;
	class NiFogProperty;
	class NiNode;
	class NiPoint3;
	class NiTexture;
	class PositionPlayerEvent;
	class QueuedFile;
	class Sky;
}

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::BSResource::Archive2
{
	class StreamOpenedEvent;
}

namespace RE
{
	class __declspec(novtable) TES
		: public BSTEventSink<BSResource::Archive2::StreamOpenedEvent>, // 00
		  public BSTEventSink<PositionPlayerEvent>						// 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TES };
		inline static constexpr auto VTABLE{ VTABLE::TES };

		using TACCallbackFuncType = void(TESObjectCELL*, void*, void*);

		enum class PICKWORLD_NODE : std::uint32_t
		{
			kActors = 1 << 0,
			kMarkers = 1 << 1,
			kLand = 1 << 2,
			kStatic = 1 << 3,
			kActive = 1 << 4,

			kAll = kActors |
				   kMarkers |
				   kLand |
				   kStatic |
				   kActive
		};

		enum class TACMode : std::int32_t
		{
			kAll = 0,
			kMainWorldOnly = 1,
			kOtherWorldsOnly = 2,
			kInteriorsOnly = 3,
			kSpecifiedWorldOnly = 4
		};

		enum class TAC_CONTROL : std::int32_t
		{
			kStop = -1,
			kContinue = 0,
			kAllStandard = 1,
			kInteriorsStandard = 2,
			kStartInCurrentCell = 3,
			kAllSaves = 4,
			kAllSavesAfterChangingObjects = 5,
			kAllRenderTest = 6,
			kInteriorsRenderTest = 7,
			kRegionFilter = 8,
			kAllFileUsage = 9,
			kAllGraphicsTest = 10,
			kAllGraphicsTestLimited = 11
		};

		class ParticleObjectCache
		{
		public:
			GAME_HEAP_REDEFINE_NEW(ParticleObjectCache);

			// members
			NiPointer<NiAVObject> model;   // 00
			NiPointer<NiAVObject>* clones; // 08
			ParticleObjectCache* next;	   // 10
		};
		static_assert(sizeof(ParticleObjectCache) == 0x18);

		~TES() override; // 00

		// override (BSTEventSink<BSResource::Archive2::StreamOpenedEvent>)
		BSEventNotifyControl ProcessEvent(const BSResource::Archive2::StreamOpenedEvent& a_event, BSTEventSource<BSResource::Archive2::StreamOpenedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent& a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override; // 01

		[[nodiscard]] static TES* GetSingleton();

		BSContainer::ForEachResult ForEachRefInSkyCell(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachRefInSkyCell(const NiPoint3& a_origin, REX::Float32 a_radius,
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;

		BSContainer::ForEachResult ForEachRef(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachRefInRange(const NiPoint3& a_center, REX::Float32 a_radius,
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachRefInRange(const TESObjectREFR* a_origin, REX::Float32 a_radius,
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;

		// members
		GridDistantArray* gridDistant;												   // 010
		GridCellArray* gridCells;													   // 018
		NiNode* objRoot;															   // 020
		NiNode* lodLandRoot;														   // 028
		NiNode* objLODWaterRoot;													   // 030
		NiDirectionalLight* objLight;												   // 038
		NiFogProperty* objFog;														   // 040
		std::int32_t currentGridX;													   // 044
		std::int32_t currentGridY;													   // 048
		std::int32_t currentQueuedX;												   // 04C
		std::int32_t currentQueuedY;												   // 050
		TESObjectCELL* interiorCell;												   // 058
		SimpleArray<TESObjectCELL*> interiorBuffer;									   // 060
		SimpleArray<TESObjectCELL*> exteriorBuffer;									   // 068
		std::uint32_t tempInteriorBufferSize;										   // 070
		std::uint32_t tempExteriorBufferSize;										   // 074
		std::int32_t saveGridX;														   // 078
		std::int32_t saveGridY;														   // 07C
		TACCallbackFuncType* tacCallbackFunc;										   // 080
		void* tacCallbackData;														   // 088
		TESRegion* tacRegionFilter;													   // 090
		Sky* sky;																	   // 098
		BSSimpleList<NiPointer<ImageSpaceModifierInstance>> activeImageSpaceModifiers; // 0A0
		std::uint32_t totalToLoad;													   // 0B0
		std::uint32_t loaded;														   // 0B4
		std::uint64_t cellCaptureStartTime;											   // 0B8
		bool disablePercentageUpdate;												   // 0C0
		bool showLANDborders;														   // 0C1
		bool fadeWhenLoading;														   // 0C2
		bool forceUpdateMultiBoundExterior;											   // 0C3
		bool collisionBoxes;														   // 0C4
		bool runningCellTests;														   // 0C5
		bool runningCellTests02;													   // 0C6
		bool runningGraphicsTests;													   // 0C7
		bool runningCellListGraphicsTests;											   // 0C8
		bool runningSubmergedObjectTest;											   // 0C9
		bool allowUnusedPurge;														   // 0CA
		REX::Float32 cellDeltaX;													   // 0D0
		REX::Float32 cellDeltaY;													   // 0D4
		TESWorldSpace* worldSpace;													   // 0D8
		BSTArray<BSTPair<TESActorBase*, std::uint16_t>> deadCount;					   // 0E0
		NiPointer<QueuedFile> preloadedAddonNodes;									   // 0F8
		NiPointer<NiTexture> bloodDecalPreload01;									   // 100
		NiPointer<QueuedFile> preloadedForms;										   // 108
		NiPointer<QueuedFile> preloadedDefaultModels;								   // 110
		ParticleObjectCache* particleCacheHead;										   // 118
		std::uint32_t placeableWaterCount;											   // 120
		NavMeshInfoMap* navMeshInfoMap;												   // 128
		NiPointer<LoadedAreaBound> loadedAreaBound;									   // 130
	};
	static_assert(sizeof(TES) == 0x138);
}
