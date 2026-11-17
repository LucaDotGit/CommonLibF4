#pragma once

#include "RE/A/AITimeStamp.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/F/FACTION_CRIME_DATA.hpp"
#include "RE/F/FACTION_DATA.hpp"
#include "RE/F/FACTION_VENDOR_DATA.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESReactionForm.hpp"

namespace RE
{
	class RANK_DATA;

	class __declspec(novtable) TESFaction :
		public TESForm,		   // 0x000
		public TESFullName,	   // 0x020
		public TESReactionForm // 0x030
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESFaction;
		inline static constexpr const auto& VTABLE = VTABLE::TESFaction;
		inline static constexpr auto FORM_TYPE = FormType::Faction;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Flags = 1 << 1,
				Reactions = 1 << 2,
				VendorData = 1 << 30,
				CrimeCounts = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTHashMap<const TESNPC*, std::uint32_t>* crimeGoldMap; // 0x50
		FACTION_DATA data;										// 0x58
		FACTION_CRIME_DATA crimeData;							// 0x60
		FACTION_VENDOR_DATA vendorData;							// 0xA8
		BSSimpleList<RANK_DATA*> rankDataList;					// 0xE0
		std::int32_t majorCrime;								// 0xF0
		std::int32_t minorCrime;								// 0xF4
		AITimeStamp resistArrestTimeStamp;						// 0xF8
		REX::Float32 enemyFlagTimeStamp;						// 0xFC
	};

	static_assert(sizeof(TESFaction) == 0x100);
}
