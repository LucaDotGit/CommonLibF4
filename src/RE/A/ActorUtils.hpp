#pragma once

namespace RE::ActorUtils
{
	[[nodiscard]]
	auto GetEquippedArmorDamageResistance(Actor* a_actor, const ActorValueInfo* a_valueInfo) -> REX::Float32;
}
