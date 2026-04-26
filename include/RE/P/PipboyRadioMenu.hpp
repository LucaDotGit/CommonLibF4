#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyRadioMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyRadioMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyRadioMenu };

		PipboyRadioMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyRadioMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02

		// members
		bool radioModeOn{ false }; // 18
	};
	static_assert(sizeof(PipboyRadioMenu) == 0x20);
}
