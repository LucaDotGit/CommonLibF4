#include "RE/R/REFR_LOCK.hpp"

#include "RE/S/Setting.hpp"
#include "RE/S/SettingUtil.hpp"

namespace RE
{
	auto REFR_LOCK::GetLockLevelMaxEasySetting() -> Setting&
	{
		static auto* MaxEasySetting = GetGameSetting("iLockLevelMaxEasy"sv);
		REX::Assert(MaxEasySetting != nullptr);
		return *MaxEasySetting;
	}

	auto REFR_LOCK::GetLockLevelMaxAverageSetting() -> Setting&
	{
		static auto* MaxAverageSetting = GetGameSetting("iLockLevelMaxAverage"sv);
		REX::Assert(MaxAverageSetting != nullptr);
		return *MaxAverageSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxHardSetting() -> Setting&
	{
		static auto* MaxHardSetting = GetGameSetting("iLockLevelMaxHard"sv);
		REX::Assert(MaxHardSetting != nullptr);
		return *MaxHardSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxVeryHardSetting() -> Setting&
	{
		static auto* MaxVeryHardSetting = GetGameSetting("iLockLevelMaxVeryHard"sv);
		REX::Assert(MaxVeryHardSetting != nullptr);
		return *MaxVeryHardSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxBarredSetting() -> Setting&
	{
		static auto* MaxBarredSetting = GetGameSetting("iLockLevelMaxBarred"sv);
		REX::Assert(MaxBarredSetting != nullptr);
		return *MaxBarredSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxChainedSetting() -> Setting&
	{
		static auto* MaxChainedSetting = GetGameSetting("iLockLevelMaxChained"sv);
		REX::Assert(MaxChainedSetting != nullptr);
		return *MaxChainedSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxTerminalSetting() -> Setting&
	{
		static auto* MaxTerminalSetting = GetGameSetting("iLockLevelMaxTerminal"sv);
		REX::Assert(MaxTerminalSetting != nullptr);
		return *MaxTerminalSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxInaccessibleSetting() -> Setting&
	{
		static auto* MaxInaccessibleSetting = GetGameSetting("iLockLevelMaxInaccessible"sv);
		REX::Assert(MaxInaccessibleSetting != nullptr);
		return *MaxInaccessibleSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxImpossibleSetting() -> Setting&
	{
		static auto* MaxImpossibleSetting = GetGameSetting("iLockLevelMaxImpossible"sv);
		REX::Assert(MaxImpossibleSetting != nullptr);
		return *MaxImpossibleSetting;
	}

	auto REFR_LOCK::GetLockLevelMaxEasy() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxEasySetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxAverage() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxAverageSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxHard() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxHardSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxVeryHard() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxVeryHardSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxBarred() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxBarredSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxChained() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxChainedSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxTerminal() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxTerminalSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxInaccessible() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxInaccessibleSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetLockLevelMaxImpossible() -> std::int32_t
	{
		const auto& setting = GetLockLevelMaxImpossibleSetting();
		if (!setting.IsInt()) [[unlikely]] {
			REX::Assert(false);
			return 0;
		}

		return setting.GetInt();
	}

	auto REFR_LOCK::GetNumericLockLevel(LOCK_LEVEL a_lockLevel) -> std::int32_t
	{
		const auto getIntSettingValue = [](const Setting& a_setting) noexcept -> std::int32_t {
			if (!a_setting.IsInt()) [[unlikely]] {
				REX::Assert(false);
				return 0;
			}

			return a_setting.GetInt();
		};

		switch (a_lockLevel) {
			case LOCK_LEVEL::Easy: {
				return getIntSettingValue(GetLockLevelMaxEasySetting());
			}
			case LOCK_LEVEL::Average: {
				return getIntSettingValue(GetLockLevelMaxAverageSetting());
			}
			case LOCK_LEVEL::Hard: {
				return getIntSettingValue(GetLockLevelMaxHardSetting());
			}
			case LOCK_LEVEL::VeryHard: {
				return getIntSettingValue(GetLockLevelMaxVeryHardSetting());
			}
			case LOCK_LEVEL::Barred: {
				return getIntSettingValue(GetLockLevelMaxBarredSetting());
			}
			case LOCK_LEVEL::Chained: {
				return getIntSettingValue(GetLockLevelMaxChainedSetting());
			}
			case LOCK_LEVEL::Terminal: {
				return getIntSettingValue(GetLockLevelMaxTerminalSetting());
			}
			case LOCK_LEVEL::Inaccessible: {
				return getIntSettingValue(GetLockLevelMaxInaccessibleSetting());
			}
			case LOCK_LEVEL::RequiresKey: {
				return getIntSettingValue(GetLockLevelMaxImpossibleSetting());
			}
			default: {
				return 0;
			}
		}
	}

	auto REFR_LOCK::GetEnumLockLevel(std::int32_t a_lockLevel) -> LOCK_LEVEL
	{
		const auto compareWithIntSetting = [](std::int32_t a_lockLevel, const Setting& a_setting) noexcept -> bool {
			if (!a_setting.IsInt()) [[unlikely]] {
				REX::Assert(false);
				return false;
			}

			return a_lockLevel <= a_setting.GetInt();
		};

		if (a_lockLevel <= 0) {
			return LOCK_LEVEL::Unlocked;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxEasySetting())) {
			return LOCK_LEVEL::Easy;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxAverageSetting())) {
			return LOCK_LEVEL::Average;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxHardSetting())) {
			return LOCK_LEVEL::Hard;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxVeryHardSetting())) {
			return LOCK_LEVEL::VeryHard;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxBarredSetting())) {
			return LOCK_LEVEL::Barred;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxChainedSetting())) {
			return LOCK_LEVEL::Chained;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxTerminalSetting())) {
			return LOCK_LEVEL::Terminal;
		}

		if (compareWithIntSetting(a_lockLevel, GetLockLevelMaxInaccessibleSetting())) {
			return LOCK_LEVEL::Inaccessible;
		}

		return LOCK_LEVEL::RequiresKey;
	}
}
