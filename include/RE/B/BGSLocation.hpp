#pragma once

#include "RE/B/BGSKeywordForm.hpp"
#include "RE/B/BSPointerHandle.hpp"
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

	class __declspec(novtable) BGSLocation
		: public TESForm,		// 000
		  public TESFullName,	// 020
		  public BGSKeywordForm // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLocation };
		inline static constexpr auto VTABLE{ VTABLE::BGSLocation };
		inline static constexpr auto FORM_TYPE{ FormType::kLocation };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kSpecialRefs = 1 << 28,
				kNewRefs = 1 << 29,
				kKeywordData = 1 << 30,
				kCleared = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kInteriorCellsUseRefLocationForWorldMapPlayerMarker = 1 << 6,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class KEYWORD_DATA
		{
		public:
			// members
			BGSKeyword* keyword; // 00
			REX::Float32 data;	 // 08
		};
		static_assert(sizeof(KEYWORD_DATA) == 0x10);

		[[nodiscard]] static auto GetLinkedLocations() -> BSTHashMap<TESFormID, BSTArray<BSTPair<TESFormID, TESFormID>>*>&;

		[[nodiscard]] bool IsChildOf(const BGSLocation* a_parent) const;
		[[nodiscard]] bool IsParentOf(const BGSLocation* a_child) const;

		// members
		BGSLocation* parentLoc;												  // 050
		TESFaction* unreportedCrimeFaction;									  // 058
		BGSMusicType* musicType;											  // 060
		BGSEncounterZone* zone;												  // 068
		ObjectRefHandle worldLocMarker;										  // 070
		REX::Float32 worldLocRadius;										  // 074
		REX::Float32 actorFadeMult;											  // 078
		ObjectRefHandle horseLocMarker;										  // 07C
		BSTArray<SpecialRefData> specialRefs;								  // 080
		BSTArray<UniqueNPCData> uniqueNPCs;									  // 098
		OverrideData* overrideData;											  // 0B0
		BSTArray<std::uint32_t> newUnloadedRefs;							  // 0B8
		BSTArray<BSTPair<BGSLocationRefType*, std::uint32_t>> newSpecialRefs; // 0D0
		NiPointer<QueuedPromoteLocationReferencesTask> promoteRefsTask;		  // 0E8
		BSTArray<ObjectRefHandle> promotedRefsArray;						  // 0F0
		volatile std::int32_t loadedCount;									  // 108
		std::uint32_t fileOffset;											  // 10C
		BSTArray<KEYWORD_DATA> keywordDataArray;							  // 110
		mutable BSSpinLock locLoadedLock;									  // 128
		std::uint32_t lastChecked;											  // 130
		bool cleared;														  // 134
		bool everCleared;													  // 135
		mutable BSReadWriteLock lock;										  // 138
	};
	static_assert(sizeof(BGSLocation) == 0x140);
}
