#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyQuestMenu : public PipboySubMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyQuestMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyQuestMenu;

		PipboyQuestMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyQuestMenu() override; // 0x00

		// override (PipboySubMenu)
		void UpdateData() override; // 0x02
	};

	static_assert(sizeof(PipboyQuestMenu) == 0x18);
}
