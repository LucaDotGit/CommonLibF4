#include "RE/R/REFR_LOCK.hpp"

#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	Setting& REFR_LOCK::GetLockLevelMaxEasySetting()
	{
		static auto* MaxEasySetting = GetGameSetting("iLockLevelMaxEasy"sv);
		return *MaxEasySetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxAverageSetting()
	{
		static auto* MaxAverageSetting = GetGameSetting("iLockLevelMaxAverage"sv);
		return *MaxAverageSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxHardSetting()
	{
		static auto* MaxHardSetting = GetGameSetting("iLockLevelMaxHard"sv);
		return *MaxHardSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxVeryHardSetting()
	{
		static auto* MaxVeryHardSetting = GetGameSetting("iLockLevelMaxVeryHard"sv);
		return *MaxVeryHardSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxBarredSetting()
	{
		static auto* MaxBarredSetting = GetGameSetting("iLockLevelMaxBarred"sv);
		return *MaxBarredSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxChainedSetting()
	{
		static auto* MaxChainedSetting = GetGameSetting("iLockLevelMaxChained"sv);
		return *MaxChainedSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxTerminalSetting()
	{
		static auto* MaxTerminalSetting = GetGameSetting("iLockLevelMaxTerminal"sv);
		return *MaxTerminalSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxInaccessibleSetting()
	{
		static auto* MaxInaccessibleSetting = GetGameSetting("iLockLevelMaxInaccessible"sv);
		return *MaxInaccessibleSetting;
	}

	Setting& REFR_LOCK::GetLockLevelMaxImpossibleSetting()
	{
		static auto* MaxImpossibleSetting = GetGameSetting("iLockLevelMaxImpossible"sv);
		return *MaxImpossibleSetting;
	}

	std::int32_t REFR_LOCK::GetNumericLockLevel(LOCK_LEVEL a_lockLevel)
	{
		const auto getIntSettingValue = [](const Setting& a_setting) noexcept -> std::int32_t {
			if (!a_setting.IsInt()) [[unlikely]] {
				REX::Assert(false);
				return 0;
			}

			return a_setting.GetInt();
		};

		switch (a_lockLevel) {
			case LOCK_LEVEL::kEasy: {
				return getIntSettingValue(GetLockLevelMaxEasySetting());
			}
			case LOCK_LEVEL::kAverage: {
				return getIntSettingValue(GetLockLevelMaxAverageSetting());
			}
			case LOCK_LEVEL::kHard: {
				return getIntSettingValue(GetLockLevelMaxHardSetting());
			}
			case LOCK_LEVEL::kVeryHard: {
				return getIntSettingValue(GetLockLevelMaxVeryHardSetting());
			}
			case LOCK_LEVEL::kBarred: {
				return getIntSettingValue(GetLockLevelMaxBarredSetting());
			}
			case LOCK_LEVEL::kChained: {
				return getIntSettingValue(GetLockLevelMaxChainedSetting());
			}
			case LOCK_LEVEL::kTerminal: {
				return getIntSettingValue(GetLockLevelMaxTerminalSetting());
			}
			case LOCK_LEVEL::kInaccessible: {
				return getIntSettingValue(GetLockLevelMaxInaccessibleSetting());
			}
			case LOCK_LEVEL::kRequiresKey: {
				return getIntSettingValue(GetLockLevelMaxImpossibleSetting());
			}
			default: {
				return 0;
			}
		}
	}

	LOCK_LEVEL REFR_LOCK::GetEnumLockLevel(std::int32_t a_lockLevel)
	{
		const auto compareWithIntSetting = [](std::int32_t a_lockLevel, const Setting& a_setting) noexcept -> bool {
			if (!a_setting.IsInt()) [[unlikely]] {
				REX::Assert(false);
				return false;
			}

			return a_lockLevel <= a_setting.GetInt();
		};

		if (a_lockLevel <= 0) {
			return LOCK_LEVEL::kUnlocked;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxEasySetting())) {
			return LOCK_LEVEL::kEasy;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxAverageSetting())) {
			return LOCK_LEVEL::kAverage;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxHardSetting())) {
			return LOCK_LEVEL::kHard;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxVeryHardSetting())) {
			return LOCK_LEVEL::kVeryHard;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxBarredSetting())) {
			return LOCK_LEVEL::kBarred;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxChainedSetting())) {
			return LOCK_LEVEL::kChained;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxTerminalSetting())) {
			return LOCK_LEVEL::kTerminal;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxInaccessibleSetting())) {
			return LOCK_LEVEL::kInaccessible;
		}

		return LOCK_LEVEL::kRequiresKey;
	}
}
