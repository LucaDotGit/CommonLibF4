#pragma once

namespace RE::AIFormulas
{
	[[nodiscard]] REX::Float32 GetBarterValue(REX::Float32 a_baseValue, REX::Float32 a_charisma, bool a_selling, TESObjectREFR* a_targetRef);
}
