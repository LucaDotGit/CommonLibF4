#pragma once

#include "RE/E/ENCOUNTER_ZONE_DATA.hpp"
#include "RE/E/ENCOUNTER_ZONE_GAME_DATA.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSEncounterZone : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSEncounterZone;
		inline static constexpr const auto& VTABLE = VTABLE::BGSEncounterZone;
		inline static constexpr auto FORM_TYPE = FormType::EncounterZone;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Flags = 1 << 1,
				GameData = static_cast<std::uint32_t>(1) << 31
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
		ENCOUNTER_ZONE_DATA data;		   // 0x20
		ENCOUNTER_ZONE_GAME_DATA gameData; // 0x38
	};

	static_assert(sizeof(BGSEncounterZone) == 0x48);
}
