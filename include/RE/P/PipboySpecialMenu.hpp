#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboySpecialMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboySpecialMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboySpecialMenu };

		PipboySpecialMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboySpecialMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02
	};
	static_assert(sizeof(PipboySpecialMenu) == 0x18);
}
