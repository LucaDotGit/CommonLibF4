#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyRadioMenu : public PipboySubMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyRadioMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyRadioMenu;

		PipboyRadioMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyRadioMenu() override; // 0x00

		// override (PipboySubMenu)
		void UpdateData() override; // 0x02

		// members
		bool radioModeOn{false}; // 0x18
	};

	static_assert(sizeof(PipboyRadioMenu) == 0x20);
}
