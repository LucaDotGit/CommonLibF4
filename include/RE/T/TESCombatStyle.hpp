#pragma once

#include "RE/C/CombatStyleCloseRangeData.hpp"
#include "RE/C/CombatStyleCoverData.hpp"
#include "RE/C/CombatStyleFlightData.hpp"
#include "RE/C/CombatStyleGeneralData.hpp"
#include "RE/C/CombatStyleLongRangeData.hpp"
#include "RE/C/CombatStyleMeleeData.hpp"
#include "RE/C/CombatStyleRangedData.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) TESCombatStyle
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESCombatStyle };
		inline static constexpr auto VTABLE{ VTABLE::TESCombatStyle };
		inline static constexpr auto FORM_TYPE{ FormType::kCombatStyle };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kAllowDualWielding = 1 << 19
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kDuelingStyle = 1 << 0,
			kFlankingStyle = 1 << 1,
			kAllowDualWielding = 1 << 2,
			kChargingStyle = 1 << 3,
			kAllowMeleeRetarget = 1 << 4,
			kUnknow05 = 1 << 5
		};

		// members
		CombatStyleGeneralData generalData;		  // 20
		CombatStyleMeleeData meleeData;			  // 50
		CombatStyleRangedData rangedData;		  // 78
		CombatStyleCloseRangeData closeRangeData; // 7C
		CombatStyleLongRangeData longRangeData;	  // A8
		CombatStyleCoverData coverData;			  // BC
		CombatStyleFlightData flightData;		  // C0
		REX::EnumSet<Flags, std::uint32_t> flags; // E0
	};
	static_assert(sizeof(TESCombatStyle) == 0xE8);
}
