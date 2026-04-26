#pragma once

namespace RE
{
	enum class QUEST_FLAGS : std::uint32_t
	{
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
		kExcludedFromExport = 1 << 9,
		kWarnOnAliasFillFailure = 1 << 10,
		kActive = 1 << 11,
		kRepeatsConditions = 1 << 12,
		kKeepInstance = 1 << 13,
		kWantDormant = 1 << 14,
		kHasDialogueData = 1 << 15,

		kNonSaveFlags = kAddIdleToHello |
						kAllowRepeatStages |
						kRunOnce |
						kExcludedFromExport |
						kWarnOnAliasFillFailure |
						kRepeatsConditions |
						kHasDialogueData
	};
}
