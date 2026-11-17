#pragma once

#include "RE/H/HolotapeMenu.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) PipboyHolotapeMenu : public HolotapeMenu // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyHolotapeMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyHolotapeMenu;
		inline static constexpr auto MENU_NAME = "PipboyHolotapeMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::PipboyHolotapeMenu;

		~PipboyHolotapeMenu() override; // 0x00

		// override (HolotapeMenu)
		void ProcessCancel() override; // 0x14

		// members
		bool wasPipboyActive; // 0x108
	};

	static_assert(sizeof(PipboyHolotapeMenu) == 0x110);
}
