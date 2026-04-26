#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::AnimationSystemUtils
{
	inline bool WillEventChangeState(const TESObjectREFR& a_ref, const BSFixedString& a_event)
	{
		using FuncType = decltype(&AnimationSystemUtils::WillEventChangeState);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::AnimationSystemUtils::WillEventChangeState };
		return std::invoke(FUNC, a_ref, a_event);
	}
}
