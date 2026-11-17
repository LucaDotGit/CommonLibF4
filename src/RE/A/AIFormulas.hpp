#pragma once

namespace RE::AIFormulas
{
	[[nodiscard]]
	auto ComputePickpocketSuccess(
		REX::Float32 a_thiefSkill,
		REX::Float32 a_targetSkill,
		std::int32_t a_valueStolen,
		REX::Float32 a_weightStolen,
		Actor* a_thief,
		Actor* a_target,
		TESForm* a_itemPickpocketing,
		bool a_placingItem) -> std::uint32_t;
	[[nodiscard]]
	auto GetBarterValue(REX::Float32 a_baseValue, REX::Float32 a_charisma, bool a_selling, TESObjectREFR* a_targetRef)
		-> REX::Float32;
}
