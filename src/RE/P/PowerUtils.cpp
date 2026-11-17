#include "RE/P/PowerUtils.hpp"

namespace RE::PowerUtils
{
	auto ItemIsPowerConnection(const TESObjectREFR* a_ref) -> bool
	{
		using FuncType = decltype(&PowerUtils::ItemIsPowerConnection);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerUtils::ItemIsPowerConnection);
		return std::invoke(FUNC, a_ref);
	}

	auto ItemIsPowerReceiver(const TESObjectREFR* a_ref) -> bool
	{
		using FuncType = decltype(&PowerUtils::ItemIsPowerReceiver);
		static const auto FUNC = REL::Relocation<FuncType>(ID::PowerUtils::ItemIsPowerReceiver);
		return std::invoke(FUNC, a_ref);
	}
}
