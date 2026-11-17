#pragma once

#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/N/NiTexture.hpp" // IWYU pragma: keep
#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyMapMenu : public PipboySubMenu // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyMapMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyMapMenu;

		PipboyMapMenu(Scaleform::GFx::Value& a_dataObj, Scaleform::GFx::Value& a_menuObj) :
			PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyMapMenu() override; // 0x00

		// override (PipboySubMenu)
		void UpdateData() override; // 0x02

		// members
		BSScaleformExternalTexture worldMapTexture; // 0x18
		Scaleform::GFx::Value mapPageObj;			// 0x30
		std::uint32_t centeredQuestMarkerID{0};		// 0x50
		std::uint32_t centeredMapMarkerID{0};		// 0x54
		std::uint32_t queuedFastTravelId{0};		// 0x58
		bool mapTexturesSentToMenu{false};			// 0x5C
		bool requestedDelayedLocalMapRender{false}; // 0x5D
	};

	static_assert(sizeof(PipboyMapMenu) == 0x60);
}
