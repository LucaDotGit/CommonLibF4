#include "RE/A/AIFormulas.hpp"

namespace RE::AIFormulas
{
	std::uint32_t ComputePickpocketSuccess(REX::Float32 a_thiefSkill, REX::Float32 a_targetSkill, std::int32_t a_valueStolen, REX::Float32 a_weightStolen, Actor* a_thief, Actor* a_target, TESForm* a_itemPickpocketing, bool a_placingItem)
	{
		using FuncType = decltype(&AIFormulas::ComputePickpocketSuccess);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::AIFormulas::ComputePickpocketSuccess };
		return std::invoke(FUNC, a_thiefSkill, a_targetSkill, a_valueStolen, a_weightStolen, a_thief, a_target, a_itemPickpocketing, a_placingItem);
	}

	REX::Float32 GetBarterValue(REX::Float32 a_baseValue, REX::Float32 a_charisma, bool a_selling, TESObjectREFR* a_targetRef)
	{
		using FuncType = decltype(&AIFormulas::GetBarterValue);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::AIFormulas::GetBarterValue };
		return std::invoke(FUNC, a_baseValue, a_charisma, a_selling, a_targetRef);
	}
}
