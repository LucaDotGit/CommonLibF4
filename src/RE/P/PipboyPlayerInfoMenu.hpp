#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyPlayerInfoMenu : public PipboySubMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyPlayerInfoMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyPlayerInfoMenu;

		PipboyPlayerInfoMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyPlayerInfoMenu() override; // 0x00

		// override (PipboySubMenu)
		void UpdateData() override; // 0x02
	};

	static_assert(sizeof(PipboyPlayerInfoMenu) == 0x18);
}
