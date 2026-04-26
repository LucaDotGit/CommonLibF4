#pragma once

namespace RE
{
	enum class QUEST_TYPE : std::int32_t;

	class QUEST_DATA
	{
	public:
		enum class Flags : std::uint16_t
		{
			kStopStart = static_cast<std::underlying_type_t<Flags>>(-1),
			kNone = 0,
			kEnabled = 1 << 0,
			kCompleted = 1 << 1,
			kAddIdleToHello = 1 << 2,
			kAllowRepeatStages = 1 << 3,
			kStartsEnabled = 1 << 4,
			kDisplayedInHUD = 1 << 5,
			kFailed = 1 << 6,
			kStageWait = 1 << 7,
			kRunOnce = 1 << 8,
			kExcludeFromExport = 1 << 9,
			kWarnOnAliasFillFailure = 1 << 10,
			kActive = 1 << 11,
			kRepeatsConditions = 1 << 12,
			kKeepInstance = 1 << 13,
			kWantDormant = 1 << 14,
			kHasDialogueData = 1 << 15
		};

		// members
		REX::Float32 questDelayTime;			  // 00
		REX::EnumSet<Flags, std::uint16_t> flags; // 04
		std::int8_t priority;					  // 06
		REX::Enum<QUEST_TYPE, std::int8_t> type;  // 07
	};
	static_assert(sizeof(QUEST_DATA) == 0x08);
}
