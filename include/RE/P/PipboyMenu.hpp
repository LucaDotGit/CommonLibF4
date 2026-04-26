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

	class __declspec(novtable) PipboyMenu
		: public GameMenuBase,					   // 000
		  public BSTEventSink<MenuOpenCloseEvent>, // 0E0
		  public BSTEventSink<IdleInputEvent>	   // 0E8
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyMenu };
		inline static constexpr auto VTABLE{ VTABLE::PipboyMenu };
		inline static constexpr auto MENU_NAME{ "PipboyMenu"sv };

		~PipboyMenu() override; // 00

		void RefreshMapMarkers(std::uint32_t a_markerID)
		{
			using FuncType = decltype(&PipboyMenu::RefreshMapMarkers);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::PipboyMenu::RefreshMapMarkers };
			FUNC(this, a_markerID);
		}

		// members
		::Scaleform::GFx::Value dataObj;		// 0F0
		PipboyStatsMenu statsMenuObj;			// 110
		PipboySpecialMenu specialMenuObj;		// 130
		PipboyPerksMenu perksMenuObj;			// 148
		PipboyInventoryMenu inventoryMenuObj;	// 160
		PipboyQuestMenu questMenuObj;			// 178
		PipboyWorkshopMenu workshopMenuObj;		// 190
		PipboyLogMenu logMenuObj;				// 1A8
		PipboyMapMenu mapMenuObj;				// 1C0
		PipboyRadioMenu radioMenuObj;			// 220
		PipboyPlayerInfoMenu playerInfoMenuObj; // 240
		std::int8_t disableInputCounter;		// 258
		bool pipboyCursorEnabled;				// 259
		bool showingModalMessage;				// 25A
		bool pipboyHiddenByAnotherMenu;			// 25B
		bool performFastTravelCheck;			// 25C
	};
	static_assert(sizeof(PipboyMenu) == 0x260);
}
