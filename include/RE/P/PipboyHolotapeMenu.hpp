#pragma once

#include "RE/H/HolotapeMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyHolotapeMenu
		: public HolotapeMenu // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyHolotapeMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyHolotapeMenu };
		inline static constexpr auto MENU_NAME{ "PipboyHolotapeMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kPipboyHolotapeMenu };

		~PipboyHolotapeMenu() override; // 00

		// override (HolotapeMenu)
		void ProcessCancel() override; // 14

		// members
		bool wasPipboyActive; // 108
	};
	static_assert(sizeof(PipboyHolotapeMenu) == 0x110);
}
