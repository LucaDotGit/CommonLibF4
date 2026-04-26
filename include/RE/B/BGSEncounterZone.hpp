#pragma once

#include "RE/E/ENCOUNTER_ZONE_DATA.hpp"
#include "RE/E/ENCOUNTER_ZONE_GAME_DATA.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSEncounterZone
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSEncounterZone };
		inline static constexpr auto VTABLE{ VTABLE::BGSEncounterZone };
		inline static constexpr auto FORM_TYPE{ FormType::kEncounterZone };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kFlags = 1 << 1,
				kGameData = 1ui32 << 31
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
		ENCOUNTER_ZONE_DATA data;		   // 20
		ENCOUNTER_ZONE_GAME_DATA gameData; // 38
	};
	static_assert(sizeof(BGSEncounterZone) == 0x48);
}
