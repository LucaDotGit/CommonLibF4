#pragma once

namespace RE
{
	class NiColor;
	class NiPoint3;
}

namespace RE::HUDMenuUtils
{
	[[nodiscard]] NiColor GetGameplayHUDColor();
	[[nodiscard]] NiColor GetGameplayHUDBackgroundColor();
	void WorldPtToScreenPt3(const NiPoint3& a_world, NiPoint3& a_screen);
	[[nodiscard]] NiPoint3 WorldPtToScreenPt3(const NiPoint3& a_world);
}
