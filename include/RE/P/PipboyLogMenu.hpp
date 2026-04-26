#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyLogMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyLogMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyLogMenu };

		PipboyLogMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyLogMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02
	};
	static_assert(sizeof(PipboyLogMenu) == 0x18);
}
