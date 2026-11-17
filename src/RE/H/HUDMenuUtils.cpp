#include "RE/H/HUDMenuUtils.hpp"

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE::HUDMenuUtils
{
	auto GetGameplayHUDColor() -> NiColor
	{
		using FuncType = decltype(&HUDMenuUtils::GetGameplayHUDColor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::HUDMenuUtils::GetGameplayHUDColor);
		return std::invoke(FUNC);
	}

	auto GetGameplayHUDBackgroundColor() -> NiColor
	{
		using FuncType = decltype(&HUDMenuUtils::GetGameplayHUDBackgroundColor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::HUDMenuUtils::GetGameplayHUDBackgroundColor);
		return std::invoke(FUNC);
	}

	void WorldPtToScreenPt3(const NiPoint3& a_world, NiPoint3& a_screen)
	{
		using FuncType = void (*)(const NiPoint3&, NiPoint3&);
		static const auto FUNC = REL::Relocation<FuncType>(ID::HUDMenuUtils::WorldPtToScreenPt3);
		std::invoke(FUNC, a_world, a_screen);
	}

	auto WorldPtToScreenPt3(const NiPoint3& a_world) -> NiPoint3
	{
		auto screen = NiPoint3();
		WorldPtToScreenPt3(a_world, screen);
		return screen;
	}
}
