#pragma once

#include "RE/H/HolotapeMenu.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class __declspec(novtable) TerminalHolotapeMenu : public HolotapeMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TerminalHolotapeMenu;
		inline static constexpr const auto& VTABLE = VTABLE::TerminalHolotapeMenu;
		inline static constexpr auto MENU_NAME = "TerminalHolotapeMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::TerminalHolotapeMenu;

		~TerminalHolotapeMenu() override; // 0x00

		// override (HolotapeMenu)
		void ProcessCancel() override;					 // 0x14
		void ProcessChatterImpl(const Params&) override; // 0x15
	};

	static_assert(sizeof(TerminalHolotapeMenu) == 0x108);
}
