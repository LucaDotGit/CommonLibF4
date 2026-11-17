#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/P/PipboyInventoryMenu.hpp"
#include "RE/P/PipboyLogMenu.hpp"
#include "RE/P/PipboyMapMenu.hpp"
#include "RE/P/PipboyPerksMenu.hpp"
#include "RE/P/PipboyPlayerInfoMenu.hpp"
#include "RE/P/PipboyQuestMenu.hpp"
#include "RE/P/PipboyRadioMenu.hpp"
#include "RE/P/PipboySpecialMenu.hpp"
#include "RE/P/PipboyStatsMenu.hpp"
#include "RE/P/PipboyWorkshopMenu.hpp"

namespace RE
{
	class IdleInputEvent;
	class MenuOpenCloseEvent;

	class __declspec(novtable) PipboyMenu :
		public GameMenuBase,					 // 0x000
		public BSTEventSink<MenuOpenCloseEvent>, // 0x0E0
		public BSTEventSink<IdleInputEvent>		 // 0x0E8
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyMenu;
		inline static constexpr auto MENU_NAME = "PipboyMenu"sv;

		~PipboyMenu() override; // 0x00

		void RefreshMapMarkers(std::uint32_t a_markerID)
		{
			using FuncType = decltype(&PipboyMenu::RefreshMapMarkers);
			static const auto FUNC = REL::Relocation<FuncType>(ID::PipboyMenu::RefreshMapMarkers);
			std::invoke(FUNC, this, a_markerID);
		}

		// members
		Scaleform::GFx::Value dataObj;			// 0x0F0
		PipboyStatsMenu statsMenuObj;			// 0x110
		PipboySpecialMenu specialMenuObj;		// 0x130
		PipboyPerksMenu perksMenuObj;			// 0x148
		PipboyInventoryMenu inventoryMenuObj;	// 0x160
		PipboyQuestMenu questMenuObj;			// 0x178
		PipboyWorkshopMenu workshopMenuObj;		// 0x190
		PipboyLogMenu logMenuObj;				// 0x1A8
		PipboyMapMenu mapMenuObj;				// 0x1C0
		PipboyRadioMenu radioMenuObj;			// 0x220
		PipboyPlayerInfoMenu playerInfoMenuObj; // 0x240
		std::int8_t disableInputCounter;		// 0x258
		bool pipboyCursorEnabled;				// 0x259
		bool showingModalMessage;				// 0x25A
		bool pipboyHiddenByAnotherMenu;			// 0x25B
		bool performFastTravelCheck;			// 0x25C
	};

	static_assert(sizeof(PipboyMenu) == 0x260);
}
