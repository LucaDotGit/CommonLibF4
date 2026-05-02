#pragma once

namespace RE::AIFormulas
{
	[[nodiscard]] std::uint32_t ComputePickpocketSuccess(REX::Float32 a_thiefSkill, REX::Float32 a_targetSkill, std::int32_t a_valueStolen, REX::Float32 a_weightStolen, Actor* a_thief, Actor* a_target, TESForm* a_itemPickpocketing, bool a_placingItem);
	[[nodiscard]] REX::Float32 GetBarterValue(REX::Float32 a_baseValue, REX::Float32 a_charisma, bool a_selling, TESObjectREFR* a_targetRef);
}
