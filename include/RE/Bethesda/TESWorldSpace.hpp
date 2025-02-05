#pragma once

#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/TESForms.hpp"
#include "RE/NetImmerse/NiPoint.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"
#include "RE/NetImmerse/NiTMap.hpp"

namespace RE
{
	class BGSTerrainManager;
	class BSMultiBoundNode;
	class BSPortalGraph;
	class NiNode;
	class QueuedPromoteLargeReferencesTask;

	struct WORLD_MAP_DATA
	{
	public:
		// members
		std::uint32_t usableWidth;	// 00
		std::uint32_t usableHeight; // 04
		std::int16_t nwCellX;		// 08
		std::int16_t nwCellY;		// 0A
		std::int16_t seCellX;		// 0C
		std::int16_t seCellY;		// 0E
	};
	static_assert(sizeof(WORLD_MAP_DATA) == 0x10);

	struct WORLD_MAP_OFFSET_DATA
	{
	public:
		// members
		float mapScale;	  // 00
		float mapOffsetX; // 04
		float mapOffsetY; // 08
		float mapOffsetZ; // 0C
	};
	static_assert(sizeof(WORLD_MAP_OFFSET_DATA) == 0x10);

	class BGSLargeRefData
	{
	public:
		struct REF_CELL_DATA
		{
		public:
			// members
			TESFormID refID;			 // 00
			std::uint32_t parentCellKey; // 04
		};
		static_assert(sizeof(REF_CELL_DATA) == 0x8);

		// members
		BSTHashMap<std::uint32_t, BSTArray<REF_CELL_DATA>*> cellOverlappingRefMap;				   // 00
		BSTHashMap<std::uint32_t, NiPointer<QueuedPromoteLargeReferencesTask>> cellPromoteTaskMap; // 30
	};
	static_assert(sizeof(BGSLargeRefData) == 0x60);

	class __declspec(novtable) TESWorldSpace
		: public TESForm,	  // 000
		  public TESFullName, // 020
		  public TESTexture	  // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWorldSpace };
		inline static constexpr auto VTABLE{ VTABLE::TESWorldSpace };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kWRLD };

		enum class Flags
		{
			kNone = 0,
			kSmallWorld = 1 << 0,
			kCannotFastTravel = 1 << 1,
			kNoLODWater = 1 << 3,
			kNoLandscape = 1 << 4,
			kNoSky = 1 << 5,
			kFixedDimensions = 1 << 6,
			kNoGrass = 1 << 7,
		};

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kPartialForm = 1 << 14,
				kCannotWait = 1 << 19
			};
		};

		enum class PARENT_USE_FLAGS
		{
			kLand = 1u << 0,
			kLOD = 1u << 1,
			kMap = 1u << 2,
			kWater = 1u << 3,
			kClimate = 1u << 4,

			kSkyCell = 1u << 6
		};

		struct ShortPoint
		{
		public:
			// members
			std::int16_t x; // 00
			std::int16_t y; // 02
		};
		static_assert(sizeof(ShortPoint) == 0x4);

		struct OFFSET_DATA
		{
		public:
			// members
			std::uint32_t* cellFileOffsets; // 00
			std::uint32_t* cellFileSizes;	// 08
			NiPoint2 offsetMinCoords;		// 10
			NiPoint2 offsetMaxCoords;		// 18
			std::uint32_t fileOffset;		// 20
		};
		static_assert(sizeof(OFFSET_DATA) == 0x28);

		[[nodiscard]] TESWorldSpace* GetParentWorld(PARENT_USE_FLAGS a_flags) const noexcept
		{
			return parentUseFlags.any(a_flags) ? parentWorld : nullptr;
		}

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept;
		[[nodiscard]] TESClimate* GetClimate() const noexcept;
		[[nodiscard]] TESObjectCELL* GetSkyCell() const noexcept;

		// members
		BSTHashMap<std::int32_t, TESObjectCELL*> cellMap;									  // 040
		TESObjectCELL* persistentCell;														  // 070
		BGSTerrainManager* terrainManager;													  // 078
		TESClimate* climate;																  // 080
		REX::EnumSet<Flags, std::int8_t> flags;												  // 088
		REX::EnumSet<PARENT_USE_FLAGS, std::uint16_t> parentUseFlags;						  // 08A
		std::int8_t worldFlags;																  // 08C
		ShortPoint fixedCenter;																  // 08E
		BSTHashMap<std::uint32_t, BSTArray<NiPointer<TESObjectREFR>>*> fixedPersistentRefMap; // 098
		BSTArray<NiPointer<TESObjectREFR>> mobilePersistentRefs;							  // 0C8
		BSTHashMap<std::uint32_t, BSSimpleList<TESObjectREFR*>*> overlappedMultiboundMap;	  // 0E0
		TESObjectCELL* skyCell;																  // 110
		BSTHashMap<std::uint32_t, BGSLocation*> locationMap;								  // 118
		BSTArray<TESObjectREFR*> teleportDoorCache;											  // 148
		NiPointer<BSPortalGraph> portalGraph;												  // 160
		BSTHashMap<ObjectRefHandle, NiPointer<BSMultiBoundNode>>* multiboundRefMap;			  // 168
		BSTHashMap<BSMultiBoundNode*, ObjectRefHandle>* refMultiboundMap;					  // 170
		NiPointer<NiNode> multiboundNode;													  // 178
		NiPointer<NiNode> portalSharedNode;													  // 180
		TESWorldSpace* parentWorld;															  // 188
		BGSLightingTemplate* lightingTemplate;												  // 190
		TESWaterForm* worldWater;															  // 198
		TESWaterForm* lodWater;																  // 1A0
		float lodWaterHeight;																  // 1A8
		WORLD_MAP_DATA worldMapData;														  // 1AC
		WORLD_MAP_OFFSET_DATA worldMapOffsetData;											  // 1BC
		BGSMusicType* musicType;															  // 1D0
		NiPoint2 minimumCoords;																  // 1D8
		NiPoint2 maximumCoords;																  // 1E0
		NiTMap<TESFile*, TESWorldSpace::OFFSET_DATA*> offsetDataMap;						  // 1E8
		BSString editorID;																	  // 208
		float defaultLandHeight;															  // 218
		float defaultWaterHeight;															  // 21C
		float distantLODMult;																  // 220
		BGSEncounterZone* encounterZone;													  // 228
		BGSLocation* location;																  // 230
		TESTexture canopyShadowTexture;														  // 238
		TESTexture waterEnvMap;																  // 248
		BGSLargeRefData largeRefData;														  // 258
		float northRotation;																  // 2B8
		std::int8_t lvlDataCellStartX;														  // 2BC
		std::int8_t lvlDataCellStartY;														  // 2BD
		std::int8_t lvlDataCellWidthX;														  // 2BE
		std::int8_t lvlDataCellWidthY;														  // 2BF
		std::int8_t* lvlDataCellA;															  // 2C0
		std::int8_t* maxHeightData;															  // 2C8
	};
	static_assert(sizeof(TESWorldSpace) == 0x2D0);
}
