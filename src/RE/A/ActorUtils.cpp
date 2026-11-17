#include "RE/A/ActorUtils.hpp"

namespace RE::ActorUtils
{
	auto GetEquippedArmorDamageResistance(Actor* a_actor, const ActorValueInfo* a_valueInfo) -> REX::Float32
	{
		using FuncType = decltype(ActorUtils::GetEquippedArmorDamageResistance);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ActorUtils::GetEquippedArmorDamageResistance);
		return std::invoke(FUNC, a_actor, a_valueInfo);
	}
}
