#pragma once

#include "RE/B/BGSLargeRefData.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/M/MemoryManager.hpp"
#include "RE/N/NiPoint.hpp"
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

	class __declspec(novtable) TESWorldSpace
		: public TESForm,	  // 00
		  public TESFullName, // 20
		  public TESTexture	  // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWorldSpace };
		inline static constexpr auto VTABLE{ VTABLE::TESWorldSpace };
		inline static constexpr auto FORM_TYPE{ FormType::kWorldSpace };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kPartialForm = 1 << 14,
				kCannotWait = 1 << 19
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kSmallWorld = 1 << 0,
			kCannotFastTravel = 1 << 1,
			kNoLODWater = 1 << 3,
			kNoLandscape = 1 << 4,
			kNoSky = 1 << 5,
			kFixedDimensions = 1 << 6,
			kNoGrass = 1 << 7
		};

		enum class PARENT_USE_FLAG : std::uint16_t
		{
			kNone = 0,
			kLand = 1 << 0,
			kLOD = 1 << 1,
			kMap = 1 << 2,
			kWater = 1 << 3,
			kClimate = 1 << 4,
			kSkyCell = 1 << 6
		};

		class ShortPoint
		{
		public:
			// members
			std::int16_t x; // 00
			std::int16_t y; // 02
		};
		static_assert(sizeof(ShortPoint) == 0x04);

		class OFFSET_DATA
		{
		public:
			GAME_HEAP_REDEFINE_NEW(OFFSET_DATA);

			[[nodiscard]] std::int32_t GetMinOffsetX() const noexcept;
			[[nodiscard]] std::int32_t GetMinOffsetY() const noexcept;
			[[nodiscard]] std::int32_t GetMaxOffsetX() const noexcept;
			[[nodiscard]] std::int32_t GetMaxOffsetY() const noexcept;

			// members
			std::uint32_t* cellFileOffsets; // 00
			std::uint32_t* cellFileSizes;	// 08
			NiPoint2 offsetMinCoords;		// 10
			NiPoint2 offsetMaxCoords;		// 18
			std::uint32_t fileOffset;		// 20
		};
		static_assert(sizeof(OFFSET_DATA) == 0x28);

		~TESWorldSpace() override; // 00

		// override (TESForm)
		bool Load(TESFile* a_file) override;		   // 09
		bool LoadPartial(TESFile* a_file) override;	   // 0A
		bool FindInFileFast(TESFile* a_file) override; // 0F

		void PrefetchCellData(TESFile* a_file, std::int32_t a_x, std::int32_t a_y, std::uint32_t a_priority);
		[[nodiscard]] bool FindCellInFile(TESFile* a_file, std::int32_t a_x, std::int32_t a_y);

		[[nodiscard]] TESWorldSpace* GetParentWorld(PARENT_USE_FLAG a_flags) const noexcept;

		[[nodiscard]] TESWaterForm* GetLODWaterType() const noexcept;
		void SetLODWaterType(TESWaterForm* a_waterType) noexcept;

		[[nodiscard]] REX::Float32 GetLODWaterHeight() const noexcept;
		void SetLODWaterHeight(REX::Float32 a_waterHeight) noexcept;

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept;
		void SetWaterType(TESWaterForm* a_waterType) noexcept;

		[[nodiscard]] REX::Float32 GetDefaultWaterHeight() const noexcept;
		void SetDefaultWaterHeight(REX::Float32 a_waterHeight) noexcept;

		[[nodiscard]] TESClimate* GetClimate() const noexcept;
		void SetClimate(TESClimate* a_climate) noexcept;

		[[nodiscard]] TESObjectCELL* GetSkyCell() const noexcept;
		void SetSkyCell(TESObjectCELL* a_skyCell) noexcept;

		[[nodiscard]] static std::int32_t GetKeyFromCellCoord(std::int32_t a_x, std::int32_t a_y) noexcept;
		[[nodiscard]] TESObjectCELL* GetCellFromKey(std::int32_t a_cellKey) const;
		[[nodiscard]] TESObjectCELL* GetCellFromCellCoord(std::int32_t a_x, std::int32_t a_y) const;

		[[nodiscard]] static std::uint32_t GetIndexForCellCoord(const OFFSET_DATA* a_offsetData, std::int32_t a_x, std::int32_t a_y) noexcept;
		[[nodiscard]] std::uint32_t GetIndexForCellCoord(TESFile* a_file, std::int32_t a_x, std::int32_t a_y) const;

		[[nodiscard]] OFFSET_DATA* GetOffsetData(TESFile* a_file) const;
		OFFSET_DATA* CreateOffsetData(TESFile* a_file);
		void FreeOffsetData(TESFile* a_file);

		// members
		BSTHashMap<std::int32_t, TESObjectCELL*> cellMap;								  // 040
		TESObjectCELL* persistentCell;													  // 070
		BGSTerrainManager* terrainManager;												  // 078
		TESClimate* climate;															  // 080
		REX::EnumSet<Flags, std::uint8_t> flags;										  // 088
		REX::EnumSet<PARENT_USE_FLAG, std::uint16_t> parentUseFlags;					  // 08A
		std::int8_t worldFlags;															  // 08C
		ShortPoint fixedCenter;															  // 08E
		BSTHashMap<TESFormID, BSTArray<NiPointer<TESObjectREFR>>*> fixedPersistentRefMap; // 098
		BSTArray<NiPointer<TESObjectREFR>> mobilePersistentRefs;						  // 0C8
		BSTHashMap<TESFormID, BSSimpleList<TESObjectREFR*>*> overlappedMultiboundMap;	  // 0E0
		TESObjectCELL* skyCell;															  // 110
		BSTHashMap<TESFormID, BGSLocation*> locationMap;								  // 118
		BSTArray<TESObjectREFR*> teleportDoorCache;										  // 148
		NiPointer<BSPortalGraph> portalGraph;											  // 160
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>>* multiboundRefMap;		  // 168
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle>* refMultiboundMap;				  // 170
		NiPointer<NiNode> multiboundNode;												  // 178
		NiPointer<NiNode> portalSharedNode;												  // 180
		TESWorldSpace* parentWorld;														  // 188
		BGSLightingTemplate* lightingTemplate;											  // 190
		TESWaterForm* worldWater;														  // 198
		TESWaterForm* lodWater;															  // 1A0
		REX::Float32 lodWaterHeight;													  // 1A8
		WORLD_MAP_DATA worldMapData;													  // 1AC
		WORLD_MAP_OFFSET_DATA worldMapOffsetData;										  // 1BC
		BGSMusicType* musicType;														  // 1D0
		NiPoint2 minimumCoords;															  // 1D8
		NiPoint2 maximumCoords;															  // 1E0
		NiTMap<TESFile*, OFFSET_DATA*> offsetDataMap;									  // 1E8
		BSString editorID;																  // 208
		REX::Float32 defaultLandHeight;													  // 218
		REX::Float32 defaultWaterHeight;												  // 21C
		REX::Float32 distantLODMult;													  // 220
		BGSEncounterZone* encounterZone;												  // 228
		BGSLocation* location;															  // 230
		TESTexture canopyShadowTexture;													  // 238
		TESTexture waterEnvMap;															  // 248
		BGSLargeRefData largeRefData;													  // 258
		REX::Float32 northRotation;														  // 2B8
		std::int8_t lvlDataCellStartX;													  // 2BC
		std::int8_t lvlDataCellStartY;													  // 2BD
		std::int8_t lvlDataCellWidthX;													  // 2BE
		std::int8_t lvlDataCellWidthY;													  // 2BF
		std::int8_t* lvlDataCells;														  // 2C0
		std::int8_t* maxHeightData;														  // 2C8
	};
	static_assert(sizeof(TESWorldSpace) == 0x2D0);
}
