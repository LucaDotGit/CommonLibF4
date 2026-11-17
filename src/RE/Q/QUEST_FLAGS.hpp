#pragma once

namespace RE
{
	enum class QUEST_FLAGS : std::uint32_t
	{
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
		ExcludedFromExport = 1 << 9,
		WarnOnAliasFillFailure = 1 << 10,
		Active = 1 << 11,
		RepeatsConditions = 1 << 12,
		KeepInstance = 1 << 13,
		WantDormant = 1 << 14,
		HasDialogueData = 1 << 15,

		NonSaveFlags = AddIdleToHello |
			AllowRepeatStages |
			RunOnce |
			ExcludedFromExport |
			WarnOnAliasFillFailure |
			RepeatsConditions |
			HasDialogueData
	};
}
