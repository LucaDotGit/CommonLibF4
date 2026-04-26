#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyPerksMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyPerksMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyPerksMenu };

		PipboyPerksMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPerksMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02
	};
	static_assert(sizeof(PipboyPerksMenu) == 0x18);
}
