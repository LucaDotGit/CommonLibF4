#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyStatsMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyStatsMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyStatsMenu };

		PipboyStatsMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyStatsMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02

		// members
		BSSoundHandle perkSound; // 18
	};
	static_assert(sizeof(PipboyStatsMenu) == 0x20);
}
