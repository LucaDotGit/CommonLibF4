#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class OverrideData;
	class QueuedPromoteLocationReferencesTask;
	class SpecialRefData;
	class UniqueNPCData;

	class __declspec(novtable) BGSLocation :
		public TESForm,		  // 0x000
		public TESFullName,	  // 0x020
		public BGSKeywordForm // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLocation;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLocation;
		inline static constexpr auto FORM_TYPE = FormType::Location;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				SpecialRefs = 1 << 28,
				NewRefs = 1 << 29,
				KeywordData = 1 << 30,
				Cleared = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				InteriorCellsUseRefLocationForWorldMapPlayerMarker = 1 << 6,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class KEYWORD_DATA
		{
		public:
			// members
			BGSKeyword* keyword; // 0x00
			REX::Float32 data;	 // 0x08
		};

		static_assert(sizeof(KEYWORD_DATA) == 0x10);

		~BGSLocation() override; // 0x00

		[[nodiscard]]
		static auto GetLinkedLocations() noexcept -> BSTHashMap<TESFormID, BSTArray<BSTPair<TESFormID, TESFormID>>*>&;

		[[nodiscard]]
		auto IsChildOf(const BGSLocation* a_parent) const -> bool;
		[[nodiscard]]
		auto IsParentOf(const BGSLocation* a_child) const -> bool;

		// members
		BGSLocation* parentLoc;												  // 0x050
		TESFaction* unreportedCrimeFaction;									  // 0x058
		BGSMusicType* musicType;											  // 0x060
		BGSEncounterZone* zone;												  // 0x068
		ObjectRefHandle worldLocMarker;										  // 0x070
		REX::Float32 worldLocRadius;										  // 0x074
		REX::Float32 actorFadeMult;											  // 0x078
		ObjectRefHandle horseLocMarker;										  // 0x07C
		BSTArray<SpecialRefData> specialRefs;								  // 0x080
		BSTArray<UniqueNPCData> uniqueNPCs;									  // 0x098
		OverrideData* overrideData;											  // 0x0B0
		BSTArray<std::uint32_t> newUnloadedRefs;							  // 0x0B8
		BSTArray<BSTPair<BGSLocationRefType*, std::uint32_t>> newSpecialRefs; // 0x0D0
		NiPointer<QueuedPromoteLocationReferencesTask> promoteRefsTask;		  // 0x0E8
		BSTArray<ObjectRefHandle> promotedRefsArray;						  // 0x0F0
		volatile std::int32_t loadedCount;									  // 0x108
		std::uint32_t fileOffset;											  // 0x10C
		BSTArray<KEYWORD_DATA> keywordDataArray;							  // 0x110
		mutable BSSpinLock locLoadedLock;									  // 0x128
		std::uint32_t lastChecked;											  // 0x130
		bool cleared;														  // 0x134
		bool everCleared;													  // 0x135
		mutable BSReadWriteLock lock;										  // 0x138
	};

	static_assert(sizeof(BGSLocation) == 0x140);
}
