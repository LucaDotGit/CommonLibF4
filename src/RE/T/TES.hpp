#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/S/SimpleArray.hpp"

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
	class GridCellArray;
	class GridDistantArray;
	class ImageSpaceModifierInstance;
	class LoadedAreaBound;
	class NavMeshInfoMap;
	class BSCullingProcess;
	class NiAVObject;
	class NiDirectionalLight;
	class NiFogProperty;
	class NiNode;
	class NiPoint3;
	class NiTexture;
	class PositionPlayerEvent;
	class QueuedFile;
	class Sky;

	class __declspec(novtable) TES :
		public BSTEventSink<BSResource::Archive2::StreamOpenedEvent>, // 0x00
		public BSTEventSink<PositionPlayerEvent>					  // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TES;
		inline static constexpr const auto& VTABLE = VTABLE::TES;

		using TACCallbackFuncType = void(TESObjectCELL*, void*, void*);

		enum class PICKWORLD_NODE : std::uint32_t
		{
			Actors = 1 << 0,
			Markers = 1 << 1,
			Land = 1 << 2,
			Static = 1 << 3,
			Active = 1 << 4
		};

		enum class TACMode : std::int32_t
		{
			All = 0,
			MainWorldOnly = 1,
			OtherWorldsOnly = 2,
			InteriorsOnly = 3,
			SpecifiedWorldOnly = 4
		};

		enum class TAC_CONTROL : std::int32_t
		{
			Stop = -1,
			Continue = 0,
			AllStandard = 1,
			InteriorsStandard = 2,
			StartInCurrentCell = 3,
			AllSaves = 4,
			AllSavesAfterChangingObjects = 5,
			AllRenderTest = 6,
			InteriorsRenderTest = 7,
			RegionFilter = 8,
			AllFileUsage = 9,
			AllGraphicsTest = 10,
			AllGraphicsTestLimited = 11
		};

		class ParticleObjectCache
		{
		public:
			GAME_HEAP_REDEFINE_NEW(ParticleObjectCache);

			// members
			NiPointer<NiAVObject> model;   // 0x00
			NiPointer<NiAVObject>* clones; // 0x08
			ParticleObjectCache* next;	   // 0x10
		};

		static_assert(sizeof(ParticleObjectCache) == 0x18);

		~TES() override; // 0x00

		// override (BSTEventSink<BSResource::Archive2::StreamOpenedEvent>)
		auto ProcessEvent(
			const BSResource::Archive2::StreamOpenedEvent& a_event,
			BSTEventSource<BSResource::Archive2::StreamOpenedEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PositionPlayerEvent>)
		auto ProcessEvent(
			const PositionPlayerEvent& a_event,
			BSTEventSource<PositionPlayerEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> TES*;

		void CreateTextureImage(
			const char* a_filePath,
			NiPointer<NiTexture>& a_outTexture,
			bool a_mustFindFile = true,
			bool a_archiveOnly = false) const;
		void UpdateMultiBoundVisibility(BSCullingProcess* a_cullingProcess);

		auto ForEachRefInSkyCell(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachRefInSkyCell(
			const NiPoint3& a_origin,
			REX::Float32 a_radius,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachRef(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachRefInRange(
			const NiPoint3& a_center,
			REX::Float32 a_radius,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachRefInRange(
			const TESObjectREFR* a_origin,
			REX::Float32 a_radius,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		// members
		GridDistantArray* gridDistant;												   // 0x010
		GridCellArray* gridCells;													   // 0x018
		NiNode* objRoot;															   // 0x020
		NiNode* lodLandRoot;														   // 0x028
		NiNode* objLODWaterRoot;													   // 0x030
		NiDirectionalLight* objLight;												   // 0x038
		NiFogProperty* objFog;														   // 0x040
		std::int32_t currentGridX;													   // 0x044
		std::int32_t currentGridY;													   // 0x048
		std::int32_t currentQueuedX;												   // 0x04C
		std::int32_t currentQueuedY;												   // 0x050
		TESObjectCELL* interiorCell;												   // 0x058
		SimpleArray<TESObjectCELL*> interiorBuffer;									   // 0x060
		SimpleArray<TESObjectCELL*> exteriorBuffer;									   // 0x068
		std::uint32_t tempInteriorBufferSize;										   // 0x070
		std::uint32_t tempExteriorBufferSize;										   // 0x074
		std::int32_t saveGridX;														   // 0x078
		std::int32_t saveGridY;														   // 0x07C
		TACCallbackFuncType* tacCallbackFunc;										   // 0x080
		void* tacCallbackData;														   // 0x088
		TESRegion* tacRegionFilter;													   // 0x090
		Sky* sky;																	   // 0x098
		BSSimpleList<NiPointer<ImageSpaceModifierInstance>> activeImageSpaceModifiers; // 0x0A0
		std::uint32_t totalToLoad;													   // 0x0B0
		std::uint32_t loaded;														   // 0x0B4
		std::uint64_t cellCaptureStartTime;											   // 0x0B8
		bool disablePercentageUpdate;												   // 0x0C0
		bool showLANDborders;														   // 0x0C1
		bool fadeWhenLoading;														   // 0x0C2
		bool forceUpdateMultiBoundExterior;											   // 0x0C3
		bool collisionBoxes;														   // 0x0C4
		bool runningCellTests;														   // 0x0C5
		bool runningCellTests02;													   // 0x0C6
		bool runningGraphicsTests;													   // 0x0C7
		bool runningCellListGraphicsTests;											   // 0x0C8
		bool runningSubmergedObjectTest;											   // 0x0C9
		bool allowUnusedPurge;														   // 0x0CA
		REX::Float32 cellDeltaX;													   // 0x0D0
		REX::Float32 cellDeltaY;													   // 0x0D4
		TESWorldSpace* worldSpace;													   // 0x0D8
		BSTArray<BSTPair<TESActorBase*, std::uint16_t>> deadCount;					   // 0x0E0
		NiPointer<QueuedFile> preloadedAddonNodes;									   // 0x0F8
		NiPointer<NiTexture> bloodDecalPreload01;									   // 0x100
		NiPointer<QueuedFile> preloadedForms;										   // 0x108
		NiPointer<QueuedFile> preloadedDefaultModels;								   // 0x110
		ParticleObjectCache* particleCacheHead;										   // 0x118
		std::uint32_t placeableWaterCount;											   // 0x120
		NavMeshInfoMap* navMeshInfoMap;												   // 0x128
		NiPointer<LoadedAreaBound> loadedAreaBound;									   // 0x130
	};

	static_assert(sizeof(TES) == 0x138);
}
