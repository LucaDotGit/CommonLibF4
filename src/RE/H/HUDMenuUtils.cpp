#include "RE/H/HUDMenuUtils.hpp"

#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE::HUDMenuUtils
{
	NiColor GetGameplayHUDColor()
	{
		using FuncType = decltype(&HUDMenuUtils::GetGameplayHUDColor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::HUDMenuUtils::GetGameplayHUDColor };
		return std::invoke(FUNC);
	}

	NiColor GetGameplayHUDBackgroundColor()
	{
		using FuncType = decltype(&HUDMenuUtils::GetGameplayHUDBackgroundColor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::HUDMenuUtils::GetGameplayHUDBackgroundColor };
		return std::invoke(FUNC);
	}

	void WorldPtToScreenPt3(const NiPoint3& a_world, NiPoint3& a_screen)
	{
		using FuncType = void (*)(const NiPoint3&, NiPoint3&);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::HUDMenuUtils::WorldPtToScreenPt3 };
		FUNC(a_world, a_screen);
	}

	NiPoint3 WorldPtToScreenPt3(const NiPoint3& a_world)
	{
		auto screen = NiPoint3();
		WorldPtToScreenPt3(a_world, screen);
		return screen;
	}
}
