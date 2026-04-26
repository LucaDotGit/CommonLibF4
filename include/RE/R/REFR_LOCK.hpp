#pragma once

#include "RE/L/LOCK_LEVEL.hpp"

namespace RE
{
	class Setting;

	class REFR_LOCK
	{
	public:
		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kLocked = 1 << 0,
			kLeveled = 1 << 2
		};

		[[nodiscard]] static Setting& GetLockLevelMaxEasySetting();
		[[nodiscard]] static Setting& GetLockLevelMaxAverageSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxHardSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxVeryHardSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxBarredSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxChainedSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxTerminalSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxInaccessibleSetting();
		[[nodiscard]] static Setting& GetLockLevelMaxImpossibleSetting();

		[[nodiscard]] static std::int32_t GetNumericLockLevel(LOCK_LEVEL a_lockLevel);
		[[nodiscard]] static LOCK_LEVEL GetEnumLockLevel(std::int32_t a_lockLevel);

		[[nodiscard]] LOCK_LEVEL GetLockLevel(const TESObjectREFR* a_owner) const
		{
			using FuncType = decltype(&REFR_LOCK::GetLockLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::REFR_LOCK::GetLockLevel };
			return std::invoke(FUNC, this, a_owner);
		}

		[[nodiscard]] bool IsLocked() const noexcept
		{
			return flags.any(Flags::kLocked);
		}

		[[nodiscard]] bool IsLeveled() const noexcept
		{
			return flags.any(Flags::kLeveled);
		}

		// members
		std::uint8_t baseLevel;					 // 00
		TESKey* key;							 // 08
		REX::EnumSet<Flags, std::uint8_t> flags; // 10
		std::uint32_t numTries;					 // 14
	};
	static_assert(sizeof(REFR_LOCK) == 0x18);
}
