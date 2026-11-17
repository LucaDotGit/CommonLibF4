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
	class __declspec(novtable) TESCombatStyle : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESCombatStyle;
		inline static constexpr const auto& VTABLE = VTABLE::TESCombatStyle;
		inline static constexpr auto FORM_TYPE = FormType::CombatStyle;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				AllowDualWielding = 1 << 19
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			DuelingStyle = 1 << 0,
			FlankingStyle = 1 << 1,
			AllowDualWielding = 1 << 2,
			ChargingStyle = 1 << 3,
			AllowMeleeRetarget = 1 << 4,
			Unknow05 = 1 << 5
		};

		// members
		CombatStyleGeneralData generalData;		  // 0x20
		CombatStyleMeleeData meleeData;			  // 0x50
		CombatStyleRangedData rangedData;		  // 0x78
		CombatStyleCloseRangeData closeRangeData; // 0x7C
		CombatStyleLongRangeData longRangeData;	  // 0xA8
		CombatStyleCoverData coverData;			  // 0xBC
		CombatStyleFlightData flightData;		  // 0xC0
		REX::EnumSet<Flags, std::uint32_t> flags; // 0xE0
	};

	static_assert(sizeof(TESCombatStyle) == 0xE8);
}
