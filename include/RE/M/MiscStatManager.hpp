#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::MiscStatManager
{
	enum class MiscStatType : std::uint32_t
	{
		kGeneral = 0,
		kQuest = 1,
		kCombat = 2,
		kCrafting = 3,
		kCrime = 4,
		kSanctuary = 5,
		kLog = 6,
		kMiniGame = 7,
		kHidden = 7,

		kTotal = 7
	};

	class MiscStat
	{
	public:
		// members
		BSFixedString id;													  // 00
		BSFixedString displayName;											  // 08
		std::int32_t value{ 0 };											  // 10
		REX::Enum<MiscStatType, std::int32_t> type{ MiscStatType::kGeneral }; // 14
		bool showIfZero{ true };											  // 18
	};
	static_assert(sizeof(MiscStat) == 0x20);

	[[nodiscard]] inline RE::BSTArray<MiscStat>& GetMiscStats()
	{
		static const auto MISC_STATS = REL::Relocation<BSTArray<MiscStat>*>{ ID::MiscStatManager::MiscStats };
		return *MISC_STATS;
	}
}
