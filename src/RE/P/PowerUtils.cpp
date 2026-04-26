#include "RE/P/PowerUtils.hpp"

namespace RE::PowerUtils
{
	bool ItemIsPowerConnection(const TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&PowerUtils::ItemIsPowerConnection);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerUtils::ItemIsPowerConnection };
		return std::invoke(FUNC, a_ref);
	}

	bool ItemIsPowerReceiver(const TESObjectREFR* a_ref)
	{
		using FuncType = decltype(&PowerUtils::ItemIsPowerReceiver);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::PowerUtils::ItemIsPowerReceiver };
		return std::invoke(FUNC, a_ref);
	}
}
