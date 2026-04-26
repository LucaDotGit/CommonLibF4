#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyInventoryMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyInventoryMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyInventoryMenu };

		PipboyInventoryMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyInventoryMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02

		void SetQuickkey(std::int32_t a_selectedIndex, std::int32_t a_quickkeyIndex)
		{
			using FuncType = decltype(&PipboyInventoryMenu::SetQuickkey);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyInventoryMenu::SetQuickkey };
			FUNC(this, a_selectedIndex, a_quickkeyIndex);
		}
	};
	static_assert(sizeof(PipboyInventoryMenu) == 0x18);
}
