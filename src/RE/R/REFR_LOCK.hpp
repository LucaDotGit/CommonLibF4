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
			None = 0,
			Locked = 1 << 0,
			Leveled = 1 << 2
		};

		[[nodiscard]]
		static auto GetLockLevelMaxEasySetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxAverageSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxHardSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxVeryHardSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxBarredSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxChainedSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxTerminalSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxInaccessibleSetting() -> Setting&;
		[[nodiscard]]
		static auto GetLockLevelMaxImpossibleSetting() -> Setting&;

		[[nodiscard]]
		static auto GetLockLevelMaxEasy() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxAverage() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxHard() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxVeryHard() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxBarred() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxChained() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxTerminal() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxInaccessible() -> std::int32_t;
		[[nodiscard]]
		static auto GetLockLevelMaxImpossible() -> std::int32_t;

		[[nodiscard]]
		static auto GetNumericLockLevel(LOCK_LEVEL a_lockLevel) -> std::int32_t;
		[[nodiscard]]
		static auto GetEnumLockLevel(std::int32_t a_lockLevel) -> LOCK_LEVEL;

		[[nodiscard]]
		auto GetLockLevel(const TESObjectREFR* a_owner) const -> LOCK_LEVEL
		{
			using FuncType = decltype(&REFR_LOCK::GetLockLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::REFR_LOCK::GetLockLevel);
			return std::invoke(FUNC, this, a_owner);
		}

		[[nodiscard]]
		auto IsLocked() const noexcept -> bool
		{
			return flags.any(Flags::Locked);
		}

		[[nodiscard]]
		auto IsLeveled() const noexcept -> bool
		{
			return flags.any(Flags::Leveled);
		}

		// members
		std::uint8_t baseLevel;					 // 0x00
		TESKey* key;							 // 0x08
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x10
		std::uint32_t numTries;					 // 0x14
	};

	static_assert(sizeof(REFR_LOCK) == 0x18);
}
