#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class bhkPickData;
	class bhkWorldM;
	class EXTERIOR_DATA;
	class ExtraDataList;
	class INTERIOR_DATA;
	class LOADED_CELL_DATA;
	class NavMeshArray;
	class NiAVObject;
	class NiPoint3;
	class TESRegionList;
}

namespace RE::BGSWaterCollisionManager
{
	class AutoWater;
	class BGSWaterUpdateI;
}

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) TESObjectCELL
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESObjectCELL };
		inline static constexpr auto VTABLE{ VTABLE::TESObjectCELL };
		inline static constexpr auto FORM_TYPE{ FormType::kCell };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kFlags = 1 << 1,
				kFullName = 1 << 2,
				kOwnership = 1 << 3,
				kExteriorShort = 1 << 28,
				kExteriorChar = 1 << 29,
				kDetachTime = 1 << 30,
				kSeenData = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kNoPreVis = 1 << 7,
				kPersistent = 1 << 10,
				kIgnored = 1 << 12,
				kOffLimits = 1 << 17,
				kCompressed = 1 << 18,
				kCannotWait = 1 << 19
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kIsInterior = 1 << 0,
			kHasWater = 1 << 1,
			kCanTravelFromHere = 1 << 2,
			kNoLODWater = 1 << 3,
			kHasTempData = 1 << 4,
			kPublicArea = 1 << 5,
			kHandChanged = 1 << 6,
			kShowSky = 1 << 7,
			kUseSkyLighting = 1 << 8,
			kWarnToLeave = 1 << 9,
			kHiddenFromInteriorList = 1 << 10,
			kSunlightShadows = 1 << 11,
			kDistantLODOnly = 1 << 12,
			kFollowersCannotTravelHere = 1 << 13
		};

		enum class CELLNODE : std::int32_t
		{
			kActor = 0,
			kMarker = 1,
			kLand = 2,
			kStatic = 3,
			kDynamic = 4,
			kOcclusionPlane = 5,
			kPortal = 6,
			kMultibound = 7,
			kCollision = 8,
			kSmallObjects = 9,
			kLightMarker = 10,
			kSoundMarker = 11
		};

		enum class CELL_CULL_NODE : std::int32_t
		{
			kActor = 0,
			kMarker = 1,
			kLand = 2,
			kStatic = 3,
			kDynamic = 4,
			kOcclusionPlane = 5,
			kPortal = 6,
			kMultibound = 7,
			kCollision = 8,
			kLightMarker = 9,
			kSoundMarker = 10,
			kWater = 11
		};

		enum class CELL_STATE : std::int32_t
		{
			kNotLoaded = 0,
			kUnloading = 1,
			kLoadingData = 2,
			kLoading = 3,
			kLoaded = 4,
			kDetaching = 5,
			kAttachQueued = 6,
			kAttaching = 7,
			kAttached = 8
		};

		enum class GameFlags : std::uint16_t
		{
		};

		enum class MARKERNODECHILD : std::int32_t
		{
			kLightMarker = 0,
			kSoundMarker = 1
		};

		enum class QUAD_HIDE_STATE : std::int32_t
		{
			kNormal = 0,
			kCulled = 1,
			kMissing = 2
		};

		~TESObjectCELL() override; // 00

		// override (TESForm)
		bool Load(TESFile* a_file) override;		   // 09
		bool FindInFileFast(TESFile* a_file) override; // 0F

		void AttachReference3D(TESObjectREFR* a_ref, bool a_onTop, bool a_queueAttach);
		void RemoveReference(TESObjectREFR* a_ref);
		void SetCullCellMarkers(bool a_cull);
		void UpdateAllDecals();
		void UpdateAllRefsLoaded();

		[[nodiscard]] std::uint32_t GetInteriorOffset() const;
		void SetInteriorOffset(std::uint32_t a_offset);

		[[nodiscard]] bool HasWater() const noexcept { return cellFlags.any(Flags::kHasWater); }
		[[nodiscard]] bool IsExterior() const noexcept { return !IsInterior(); }
		[[nodiscard]] bool IsInterior() const noexcept { return cellFlags.any(Flags::kIsInterior); }
		[[nodiscard]] bool IsAttached() const noexcept { return cellState.any(CELL_STATE::kAttached); }

		[[nodiscard]] EXTERIOR_DATA* GetExteriorData() const noexcept { return IsExterior() ? exteriorData : nullptr; }
		[[nodiscard]] INTERIOR_DATA* GetInteriorData() const noexcept { return IsInterior() ? interiorData : nullptr; }
		[[nodiscard]] TESWorldSpace* GetWorldSpace() const noexcept { return IsExterior() ? worldSpace : nullptr; }

		[[nodiscard]] auto GetCellX() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]] auto GetCellY() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]] auto GetCellXAndY() const noexcept -> std::optional<std::tuple<std::int32_t, std::int32_t>>;

		[[nodiscard]] auto GetDataX() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]] auto GetDataY() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]] auto GetDataXAndY() const noexcept -> std::optional<std::tuple<std::int32_t, std::int32_t>>;

		[[nodiscard]] auto GetWorldX() const noexcept -> std::optional<REX::Float32>;
		[[nodiscard]] auto GetWorldY() const noexcept -> std::optional<REX::Float32>;
		[[nodiscard]] auto GetWorldXAndY() const noexcept -> std::optional<std::tuple<REX::Float32, REX::Float32>>;

		[[nodiscard]] TESWaterForm* GetWaterType() const noexcept;
		[[nodiscard]] REX::Float32 GetExteriorWaterHeight() const noexcept;

		[[nodiscard]] BSTSmartPointer<ExtraDataList> GetOrCreateExtraList();

		BSContainer::ForEachResult ForEachRef(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachRefInRange(const NiPoint3& a_origin, REX::Float32 a_radius,
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)>>& a_predicate) const;

		// members
		mutable BSSpinLock grassCreateLock;			  // 30
		mutable BSSpinLock grassTaskLock;			  // 38
		REX::EnumSet<Flags, std::uint16_t> cellFlags; // 40
		std::uint16_t cellGameFlags;				  // 42
		REX::Enum<CELL_STATE, std::int8_t> cellState; // 44
		bool autoWaterLoaded;						  // 45
		bool cellDetached;							  // 46
		BSTSmartPointer<ExtraDataList> extraList;	  // 48
		union
		{
			EXTERIOR_DATA* exteriorData;
			INTERIOR_DATA* interiorData;
		}; // 50
		TESObjectLAND* cellLand;													 // 58
		REX::Float32 waterHeight;													 // 60
		NavMeshArray* navMeshes;													 // 68
		BSTArray<NiPointer<TESObjectREFR>> references;								 // 70
		BSTSmartPointer<BGSWaterCollisionManager::AutoWater> autoWater;				 // 77
		BSTSet<BSTSmartPointer<BGSWaterCollisionManager::BGSWaterUpdateI>> waterSet; // 80
		mutable BSSpinLock spinLock;												 // C0
		union
		{
			TESWorldSpace* worldSpace;
			std::uint32_t tempDataOffset;
		}; // C8
		LOADED_CELL_DATA* loadedData;		   // D0
		BGSLightingTemplate* lightingTemplate; // D8
		void* visibilityData;				   // E0 - TODO: `BSResource::RHandleType<BSResource::Entry<BSTSmartPointer<BSPrecomputedVisibility::CellVisibilityData, BSTSmartPointerIntrusiveRefCount>, BSResource::EntryDBTraits<BSPrecomputedVisibility::BSVisDB::DBTraits, BSResource::EntryDB<BSPrecomputedVisibility::BSVisDB::DBTraits>>::CArgs>, BSResource::EntryDB<BSPrecomputedVisibility::BSVisDB::DBTraits>>`
		std::uint32_t rootVisibilityCellID;	   // E8
		std::uint16_t visCalcDate;			   // EC
		std::uint16_t preCombineDate;		   // F0
	};
	static_assert(sizeof(TESObjectCELL) == 0xF0);
}
