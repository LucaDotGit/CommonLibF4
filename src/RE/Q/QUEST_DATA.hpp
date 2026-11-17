#pragma once

namespace RE
{
	enum class QUEST_TYPE : std::int32_t;

	class QUEST_DATA
	{
	public:
		enum class Flags : std::uint16_t
		{
			StopStart = static_cast<std::underlying_type_t<Flags>>(-1),
			None = 0,
			Enabled = 1 << 0,
			Completed = 1 << 1,
			AddIdleToHello = 1 << 2,
			AllowRepeatStages = 1 << 3,
			StartsEnabled = 1 << 4,
			DisplayedInHUD = 1 << 5,
			Failed = 1 << 6,
			StageWait = 1 << 7,
			RunOnce = 1 << 8,
			ExcludeFromExport = 1 << 9,
			WarnOnAliasFillFailure = 1 << 10,
			Active = 1 << 11,
			RepeatsConditions = 1 << 12,
			KeepInstance = 1 << 13,
			WantDormant = 1 << 14,
			HasDialogueData = 1 << 15
		};

		// members
		REX::Float32 questDelayTime;			  // 0x00
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x04
		std::int8_t priority;					  // 0x06
		REX::Enum<QUEST_TYPE, std::int8_t> type;  // 0x07
	};

	static_assert(sizeof(QUEST_DATA) == 0x08);
}
