#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyWorkshopMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyWorkshopMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyWorkshopMenu };

		PipboyWorkshopMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyWorkshopMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override;
	};
	static_assert(sizeof(PipboyWorkshopMenu) == 0x18);
}
