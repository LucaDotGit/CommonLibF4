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

	class __declspec(novtable) TESFaction
		: public TESForm,		 // 000
		  public TESFullName,	 // 020
		  public TESReactionForm // 030
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESFaction };
		inline static constexpr auto VTABLE{ VTABLE::TESFaction };
		inline static constexpr auto FORM_TYPE{ FormType::kFaction };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kFlags = 1 << 1,
				kReactions = 1 << 2,
				kVendorData = 1 << 30,
				kCrimeCounts = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTHashMap<const TESNPC*, std::uint32_t>* crimeGoldMap; // 50
		FACTION_DATA data;										// 58
		FACTION_CRIME_DATA crimeData;							// 60
		FACTION_VENDOR_DATA vendorData;							// A8
		BSSimpleList<RANK_DATA*> rankDataList;					// E0
		std::int32_t majorCrime;								// F0
		std::int32_t minorCrime;								// F4
		AITimeStamp resistArrestTimeStamp;						// F8
		REX::Float32 enemyFlagTimeStamp;						// FC
	};
	static_assert(sizeof(TESFaction) == 0x100);
}
