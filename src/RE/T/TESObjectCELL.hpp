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
	class NiPoint2;
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
	class __declspec(novtable) TESObjectCELL :
		public TESForm,	   // 0x00
		public TESFullName // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectCELL;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectCELL;
		inline static constexpr auto FORM_TYPE = FormType::Cell;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Flags = 1 << 1,
				FullName = 1 << 2,
				Ownership = 1 << 3,
				ExteriorShort = 1 << 28,
				ExteriorChar = 1 << 29,
				DetachTime = 1 << 30,
				SeenData = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				NoPreVis = 1 << 7,
				Persistent = 1 << 10,
				Ignored = 1 << 12,
				OffLimits = 1 << 17,
				Compressed = 1 << 18,
				CannotWait = 1 << 19
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint16_t
		{
			None = 0,
			IsInterior = 1 << 0,
			HasWater = 1 << 1,
			CanTravelFromHere = 1 << 2,
			NoLODWater = 1 << 3,
			HasTempData = 1 << 4,
			PublicArea = 1 << 5,
			HandChanged = 1 << 6,
			ShowSky = 1 << 7,
			UseSkyLighting = 1 << 8,
			WarnToLeave = 1 << 9,
			HiddenFromInteriorList = 1 << 10,
			SunlightShadows = 1 << 11,
			DistantLODOnly = 1 << 12,
			FollowersCannotTravelHere = 1 << 13
		};

		enum class CELLNODE : std::int32_t
		{
			Actor = 0,
			Marker = 1,
			Land = 2,
			Static = 3,
			Dynamic = 4,
			OcclusionPlane = 5,
			Portal = 6,
			Multibound = 7,
			Collision = 8,
			SmallObjects = 9,
			LightMarker = 10,
			SoundMarker = 11
		};

		enum class CELL_CULL_NODE : std::int32_t
		{
			Actor = 0,
			Marker = 1,
			Land = 2,
			Static = 3,
			Dynamic = 4,
			OcclusionPlane = 5,
			Portal = 6,
			Multibound = 7,
			Collision = 8,
			LightMarker = 9,
			SoundMarker = 10,
			Water = 11
		};

		enum class CELL_STATE : std::int32_t
		{
			NotLoaded = 0,
			Unloading = 1,
			LoadingData = 2,
			Loading = 3,
			Loaded = 4,
			Detaching = 5,
			AttachQueued = 6,
			Attaching = 7,
			Attached = 8
		};

		enum class GameFlags : std::uint16_t
		{
		};

		enum class MARKERNODECHILD : std::int32_t
		{
			LightMarker = 0,
			SoundMarker = 1
		};

		enum class QUAD_HIDE_STATE : std::int32_t
		{
			Normal = 0,
			Culled = 1,
			Missing = 2
		};

		~TESObjectCELL() override; // 0x00

		// override (TESForm)
		auto Load(TESFile* a_file) -> bool override;		   // 0x09
		auto FindInFileFast(TESFile* a_file) -> bool override; // 0x0F

		void AttachReference3D(TESObjectREFR* a_ref, bool a_onTop, bool a_queueAttach);
		void RemoveReference(TESObjectREFR* a_ref);
		void SetCullCellMarkers(bool a_cull);
		void UpdateAllDecals();
		void UpdateAllRefsLoaded();

		[[nodiscard]]
		auto GetInteriorOffset() const -> std::uint32_t;
		void SetInteriorOffset(std::uint32_t a_offset);

		[[nodiscard]]
		auto HasWater() const noexcept -> bool
		{
			return cellFlags.any(Flags::HasWater);
		}

		[[nodiscard]]
		auto IsExterior() const noexcept -> bool
		{
			return !IsInterior();
		}

		[[nodiscard]]
		auto IsInterior() const noexcept -> bool
		{
			return cellFlags.any(Flags::IsInterior);
		}

		[[nodiscard]]
		auto IsAttached() const noexcept -> bool
		{
			return cellState.any(CELL_STATE::Attached);
		}

		[[nodiscard]]
		auto GetExteriorData() const noexcept -> EXTERIOR_DATA*
		{
			return IsExterior() ? exteriorData : nullptr;
		}

		[[nodiscard]]
		auto GetInteriorData() const noexcept -> INTERIOR_DATA*
		{
			return IsInterior() ? interiorData : nullptr;
		}

		[[nodiscard]]
		auto GetWorldSpace() const noexcept -> TESWorldSpace*
		{
			return IsExterior() ? worldSpace : nullptr;
		}

		[[nodiscard]]
		auto GetCellX() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]]
		auto GetCellY() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]]
		auto GetCellXAndY() const noexcept -> std::optional<REX::Vector<std::int32_t, 2>>;

		[[nodiscard]]
		auto GetDataX() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]]
		auto GetDataY() const noexcept -> std::optional<std::int32_t>;
		[[nodiscard]]
		auto GetDataXAndY() const noexcept -> std::optional<REX::Vector<std::int32_t, 2>>;

		[[nodiscard]]
		auto GetWorldX() const noexcept -> std::optional<REX::Float32>;
		[[nodiscard]]
		auto GetWorldY() const noexcept -> std::optional<REX::Float32>;
		[[nodiscard]]
		auto GetWorldXAndY() const noexcept -> std::optional<NiPoint2>;

		[[nodiscard]]
		auto GetWaterType() const noexcept -> TESWaterForm*;
		[[nodiscard]]
		auto GetExteriorWaterHeight() const noexcept -> REX::Float32;

		[[nodiscard]]
		auto GetOrCreateExtraList() -> BSTSmartPointer<ExtraDataList>;

		auto ForEachRef(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachRefInRange(
			const NiPoint3& a_origin,
			REX::Float32 a_radius,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<TESObjectREFR>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		// members
		mutable BSSpinLock grassCreateLock;			  // 0x30
		mutable BSSpinLock grassTaskLock;			  // 0x38
		REX::EnumSet<Flags, std::uint16_t> cellFlags; // 0x40
		std::uint16_t cellGameFlags;				  // 0x42
		REX::Enum<CELL_STATE, std::int8_t> cellState; // 0x44
		bool autoWaterLoaded;						  // 0x45
		bool cellDetached;							  // 0x46
		BSTSmartPointer<ExtraDataList> extraList;	  // 0x48

		union
		{
		public:
			EXTERIOR_DATA* exteriorData;
			INTERIOR_DATA* interiorData;
		}; // 0x50

		TESObjectLAND* cellLand;													 // 0x58
		REX::Float32 waterHeight;													 // 0x60
		NavMeshArray* navMeshes;													 // 0x68
		BSTArray<NiPointer<TESObjectREFR>> references;								 // 0x70
		BSTSmartPointer<BGSWaterCollisionManager::AutoWater> autoWater;				 // 0x77
		BSTSet<BSTSmartPointer<BGSWaterCollisionManager::BGSWaterUpdateI>> waterSet; // 0x80
		mutable BSSpinLock spinLock;												 // 0xC0

		union
		{
		public:
			TESWorldSpace* worldSpace;
			std::uint32_t tempDataOffset;
		}; // 0xC8

		LOADED_CELL_DATA* loadedData;		   // 0xD0
		BGSLightingTemplate* lightingTemplate; // 0xD8
		void*
			visibilityData; // 0xE0 - To-Do:
							// `BSResource::RHandleType<BSResource::Entry<BSTSmartPointer<BSPrecomputedVisibility::CellVisibilityData,
							// BSTSmartPointerIntrusiveRefCount>,
							// BSResource::EntryDBTraits<BSPrecomputedVisibility::BSVisDB::DBTraits,
							// BSResource::EntryDB<BSPrecomputedVisibility::BSVisDB::DBTraits>>::CArgs>,
							// BSResource::EntryDB<BSPrecomputedVisibility::BSVisDB::DBTraits>>`
		std::uint32_t rootVisibilityCellID; // 0xE8
		std::uint16_t visCalcDate;			// 0xEC
		std::uint16_t preCombineDate;		// 0xF0
	};

	static_assert(sizeof(TESObjectCELL) == 0xF0);
}
