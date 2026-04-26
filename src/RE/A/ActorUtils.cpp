#include "RE/A/ActorUtils.hpp"

namespace RE::ActorUtils
{
	REX::Float32 GetEquippedArmorDamageResistance(Actor* a_actor, const ActorValueInfo* a_valueInfo)
	{
		using FuncType = decltype(ActorUtils::GetEquippedArmorDamageResistance);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ActorUtils::GetEquippedArmorDamageResistance };
		return std::invoke(FUNC, a_actor, a_valueInfo);
	}
}
