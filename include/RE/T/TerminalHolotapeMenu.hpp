#pragma once

#include "RE/H/HolotapeMenu.hpp"

namespace RE
{
	class __declspec(novtable) TerminalHolotapeMenu
		: public HolotapeMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TerminalHolotapeMenu };
		inline static constexpr auto VTABLE{ VTABLE::TerminalHolotapeMenu };
		inline static constexpr auto MENU_NAME{ "TerminalHolotapeMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kTerminalHolotapeMenu };

		~TerminalHolotapeMenu() override; // 00

		// override (HolotapeMenu)
		void ProcessCancel() override;					 // 14
		void ProcessChatterImpl(const Params&) override; // 15
	};
	static_assert(sizeof(TerminalHolotapeMenu) == 0x108);
}
