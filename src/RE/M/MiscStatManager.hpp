#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::MiscStatManager
{
	enum class MiscStatType : std::int32_t
	{
		General = 0,
		Quest = 1,
		Combat = 2,
		Crafting = 3,
		Crime = 4,
		Sanctuary = 5,
		Log = 6,
		MiniGame = 7,
		Hidden = 7,

		_Count = 7
	};

	class MiscStat
	{
	public:
		// members
		BSFixedString id;												   // 0x00
		BSFixedString displayName;										   // 0x08
		std::int32_t value{0};											   // 0x10
		REX::Enum<MiscStatType, std::int32_t> type{MiscStatType::General}; // 0x14
		bool showIfZero{true};											   // 0x18
	};

	static_assert(sizeof(MiscStat) == 0x20);

	[[nodiscard]]
	inline auto GetMiscStats() noexcept -> BSTArray<MiscStat>&
	{
		static const auto MISC_STATS = REL::Relocation<BSTArray<MiscStat>*>(ID::MiscStatManager::MiscStats);
		return *MISC_STATS;
	}
}
