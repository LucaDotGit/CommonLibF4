#pragma once

#include "RE/B/BGSLargeRefData.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSString.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTMap.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"
#include "RE/W/WORLD_MAP_DATA.hpp"
#include "RE/W/WORLD_MAP_OFFSET_DATA.hpp"

namespace RE
{
	class BGSTerrainManager;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class NiNode;
	class NiPoint3;

	class __declspec(novtable) TESWorldSpace :
		public TESForm,		// 0x00
		public TESFullName, // 0x20
		public TESTexture	// 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWorldSpace;
		inline static constexpr const auto& VTABLE = VTABLE::TESWorldSpace;
		inline static constexpr auto FORM_TYPE = FormType::WorldSpace;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				PartialForm = 1 << 14,
				CannotWait = 1 << 19
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			None = 0,
			SmallWorld = 1 << 0,
			CannotFastTravel = 1 << 1,
			NoLODWater = 1 << 3,
			NoLandscape = 1 << 4,
			NoSky = 1 << 5,
			FixedDimensions = 1 << 6,
			NoGrass = 1 << 7
		};

		enum class PARENT_USE_FLAG : std::uint16_t
		{
			None = 0,
			Land = 1 << 0,
			LOD = 1 << 1,
			Map = 1 << 2,
			Water = 1 << 3,
			Climate = 1 << 4,
			SkyCell = 1 << 6
		};

		class ShortPoint
		{
		public:
			// members
			std::int16_t x; // 0x00
			std::int16_t y; // 0x02
		};

		static_assert(sizeof(ShortPoint) == 0x04);

		class OFFSET_DATA
		{
		public:
			GAME_HEAP_REDEFINE_NEW(OFFSET_DATA);

			[[nodiscard]]
			auto GetMinOffsetX() const noexcept -> std::int32_t;
			[[nodiscard]]
			auto GetMinOffsetY() const noexcept -> std::int32_t;
			[[nodiscard]]
			auto GetMaxOffsetX() const noexcept -> std::int32_t;
			[[nodiscard]]
			auto GetMaxOffsetY() const noexcept -> std::int32_t;

			// members
			std::uint32_t* cellFileOffsets; // 0x00
			std::uint32_t* cellFileSizes;	// 0x08
			NiPoint2 offsetMinCoords;		// 0x10
			NiPoint2 offsetMaxCoords;		// 0x18
			std::uint32_t fileOffset;		// 0x20
		};

		static_assert(sizeof(OFFSET_DATA) == 0x28);

		~TESWorldSpace() override; // 0x00

		// override (TESForm)
		auto Load(TESFile* a_file) -> bool override;		   // 0x09
		auto LoadPartial(TESFile* a_file) -> bool override;	   // 0x0A
		auto FindInFileFast(TESFile* a_file) -> bool override; // 0x0F

		void PrefetchCellData(TESFile* a_file, std::int32_t a_x, std::int32_t a_y, std::uint32_t a_priority);
		[[nodiscard]]
		auto FindCellInFile(TESFile* a_file, std::int32_t a_x, std::int32_t a_y) -> bool;

		void ChangeMapMarkerPosition(NiPoint3 a_position, bool a_inverse = false) noexcept;

		[[nodiscard]]
		auto GetParentWorld(PARENT_USE_FLAG a_flags) const noexcept -> TESWorldSpace*;

		[[nodiscard]]
		auto GetLODWaterType() const noexcept -> TESWaterForm*;
		void SetLODWaterType(TESWaterForm* a_waterType) noexcept;

		[[nodiscard]]
		auto GetLODWaterHeight() const noexcept -> REX::Float32;
		void SetLODWaterHeight(REX::Float32 a_waterHeight) noexcept;

		[[nodiscard]]
		auto GetWaterType() const noexcept -> TESWaterForm*;
		void SetWaterType(TESWaterForm* a_waterType) noexcept;

		[[nodiscard]]
		auto GetDefaultWaterHeight() const noexcept -> REX::Float32;
		void SetDefaultWaterHeight(REX::Float32 a_waterHeight) noexcept;

		[[nodiscard]]
		auto GetClimate() const noexcept -> TESClimate*;
		void SetClimate(TESClimate* a_climate) noexcept;

		[[nodiscard]]
		auto GetSkyCell() const noexcept -> TESObjectCELL*;
		void SetSkyCell(TESObjectCELL* a_skyCell) noexcept;

		[[nodiscard]]
		static auto GetKeyFromCellPosition(std::int32_t a_x, std::int32_t a_y) noexcept -> std::int32_t;

		[[nodiscard]]
		static auto GetKeyFromCell(const TESObjectCELL* a_cell) noexcept -> std::optional<std::int32_t>;

		[[nodiscard]]
		auto GetCellFromKey(std::int32_t a_cellKey) const -> TESObjectCELL*;

		[[nodiscard]]
		static auto GetIndexForCellPosition(const OFFSET_DATA* a_offsetData, std::int32_t a_x, std::int32_t a_y)
			noexcept -> std::uint32_t;

		[[nodiscard]]
		auto GetOffsetData(TESFile* a_file) const -> OFFSET_DATA*;
		auto CreateOffsetData(TESFile* a_file) -> OFFSET_DATA*;
		void FreeOffsetData(TESFile* a_file);

		// members
		BSTHashMap<std::int32_t, TESObjectCELL*> cellMap;								  // 0x040
		TESObjectCELL* persistentCell;													  // 0x070
		BGSTerrainManager* terrainManager;												  // 0x078
		TESClimate* climate;															  // 0x080
		REX::EnumSet<Flags, std::uint8_t> flags;										  // 0x088
		REX::EnumSet<PARENT_USE_FLAG, std::uint16_t> parentUseFlags;					  // 0x08A
		std::int8_t worldFlags;															  // 0x08C
		ShortPoint fixedCenter;															  // 0x08E
		BSTHashMap<TESFormID, BSTArray<NiPointer<TESObjectREFR>>*> fixedPersistentRefMap; // 0x098
		BSTArray<NiPointer<TESObjectREFR>> mobilePersistentRefs;						  // 0x0C8
		BSTHashMap<TESFormID, BSSimpleList<TESObjectREFR*>*> overlappedMultiboundMap;	  // 0x0E0
		TESObjectCELL* skyCell;															  // 0x110
		BSTHashMap<TESFormID, BGSLocation*> locationMap;								  // 0x118
		BSTArray<TESObjectREFR*> teleportDoorCache;										  // 0x148
		NiPointer<BSPortalGraph> portalGraph;											  // 0x160
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>>* multiboundRefMap;		  // 0x168
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle>* refMultiboundMap;				  // 0x170
		NiPointer<NiNode> multiboundNode;												  // 0x178
		NiPointer<NiNode> portalSharedNode;												  // 0x180
		TESWorldSpace* parentWorld;														  // 0x188
		BGSLightingTemplate* lightingTemplate;											  // 0x190
		TESWaterForm* worldWater;														  // 0x198
		TESWaterForm* lodWater;															  // 0x1A0
		REX::Float32 lodWaterHeight;													  // 0x1A8
		WORLD_MAP_DATA worldMapData;													  // 0x1AC
		WORLD_MAP_OFFSET_DATA worldMapOffsetData;										  // 0x1BC
		BGSMusicType* musicType;														  // 0x1D0
		NiPoint2 minimumCoords;															  // 0x1D8
		NiPoint2 maximumCoords;															  // 0x1E0
		NiTMap<TESFile*, OFFSET_DATA*> offsetDataMap;									  // 0x1E8
		BSString editorID;																  // 0x208
		REX::Float32 defaultLandHeight;													  // 0x218
		REX::Float32 defaultWaterHeight;												  // 0x21C
		REX::Float32 distantLODMult;													  // 0x220
		BGSEncounterZone* encounterZone;												  // 0x228
		BGSLocation* location;															  // 0x230
		TESTexture canopyShadowTexture;													  // 0x238
		TESTexture waterEnvMap;															  // 0x248
		BGSLargeRefData largeRefData;													  // 0x258
		REX::Float32 northRotation;														  // 0x2B8
		std::int8_t lvlDataCellStartX;													  // 0x2BC
		std::int8_t lvlDataCellStartY;													  // 0x2BD
		std::int8_t lvlDataCellWidthX;													  // 0x2BE
		std::int8_t lvlDataCellWidthY;													  // 0x2BF
		std::int8_t* lvlDataCells;														  // 0x2C0
		std::int8_t* maxHeightData;														  // 0x2C8
	};

	static_assert(sizeof(TESWorldSpace) == 0x2D0);
}
