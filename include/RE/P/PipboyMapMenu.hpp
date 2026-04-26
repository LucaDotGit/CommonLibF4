#pragma once

#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/N/NiTexture.hpp" // IWYU pragma: keep
#include "RE/P/PipboySubMenu.hpp"

namespace RE
{
	class __declspec(novtable) PipboyMapMenu
		: public PipboySubMenu // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyMapMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyMapMenu };

		PipboyMapMenu(::Scaleform::GFx::Value& a_dataObj, ::Scaleform::GFx::Value& a_menuObj)
			: PipboySubMenu(a_dataObj, a_menuObj)
		{
			REL::EmplaceVtable(this);
		}

		~PipboyMapMenu() override; // 00

		// override (PipboySubMenu)
		void UpdateData() override; // 02

		// members
		BSScaleformExternalTexture worldMapTexture;	  // 18
		::Scaleform::GFx::Value mapPageObj;			  // 30
		std::uint32_t centeredQuestMarkerID{ 0 };	  // 50
		std::uint32_t centeredMapMarkerID{ 0 };		  // 54
		std::uint32_t queuedFastTravelId{ 0 };		  // 58
		bool mapTexturesSentToMenu{ false };		  // 5C
		bool requestedDelayedLocalMapRender{ false }; // 5D
	};
	static_assert(sizeof(PipboyMapMenu) == 0x60);
}
