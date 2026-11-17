#pragma once

namespace RE
{
	class NiColor;
	class NiPoint3;
}

namespace RE::HUDMenuUtils
{
	[[nodiscard]]
	auto GetGameplayHUDColor() -> NiColor;
	[[nodiscard]]
	auto GetGameplayHUDBackgroundColor() -> NiColor;
	void WorldPtToScreenPt3(const NiPoint3& a_world, NiPoint3& a_screen);
	[[nodiscard]]
	auto WorldPtToScreenPt3(const NiPoint3& a_world) -> NiPoint3;
}
