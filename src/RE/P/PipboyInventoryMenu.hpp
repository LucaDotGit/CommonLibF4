#pragma once

#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyInventoryMenu : public PipboySubMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyInventoryMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyInventoryMenu;

		PipboyInventoryMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyInventoryMenu() override; // 0x00

		// override (PipboySubMenu)
		void UpdateData() override; // 0x02

		void SetQuickkey(std::int32_t a_selectedIndex, std::int32_t a_quickkeyIndex)
		{
			using FuncType = decltype(&PipboyInventoryMenu::SetQuickkey);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryMenu::SetQuickkey);
			std::invoke(FUNC, this, a_selectedIndex, a_quickkeyIndex);
		}

		void SortItems(std::uint32_t a_filterIndex)
		{
			using FuncType = decltype(&PipboyInventoryMenu::SortItems);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyInventoryMenu::SortItems);
			std::invoke(FUNC, this, a_filterIndex);
		}
	};

	static_assert(sizeof(PipboyInventoryMenu) == 0x18);
}
