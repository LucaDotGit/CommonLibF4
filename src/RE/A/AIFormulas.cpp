#include "RE/A/AIFormulas.hpp"

namespace RE::AIFormulas
{
	REX::Float32 GetBarterValue(REX::Float32 a_baseValue, REX::Float32 a_charisma, bool a_selling, TESObjectREFR* a_targetRef)
	{
		using FuncType = decltype(&AIFormulas::GetBarterValue);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::AIFormulas::GetBarterValue };
		return std::invoke(FUNC, a_baseValue, a_charisma, a_selling, a_targetRef);
	}
}
