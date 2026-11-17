#pragma once

namespace RE::PowerUtils
{
	[[nodiscard]]
	auto ItemIsPowerConnection(const TESObjectREFR* a_ref) -> bool;
	[[nodiscard]]
	auto ItemIsPowerReceiver(const TESObjectREFR* a_ref) -> bool;
}
