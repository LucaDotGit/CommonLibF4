#pragma once

#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/S/StartMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class MenuOpenCloseEvent;

	class MainMenu
		: public StartMenuBase,					  // 000
		  public BSTEventSink<MenuOpenCloseEvent> // 228
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MainMenu };
		inline static constexpr auto VTABLE{ VTABLE::MainMenu };
		inline static constexpr auto MENU_NAME{ "MainMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kMainMenu };

		enum class MAIN_MENU_EXIT_CONDITION : std::int32_t
		{
			kNoExit = 0,
			kNewGame = 1,
			kContinue = 2,
			kLoadGame = 3
		};

		~MainMenu() override; // 00

		// members
		MAIN_MENU_EXIT_CONDITION mainMenuExitCondition;				 // 230
		BSTSet<std::uint32_t> ownedDLC;								 // 238
		std::uint64_t creationTime;									 // 268
		std::int32_t queuedLoadIndex;								 // 270
		bool choseContinue;											 // 274
		bool queueStartNewGame;										 // 275
		bool queueContinueGame;										 // 276
		bool creditScreen;											 // 277
		bool userEngaged;											 // 278
		bool mainBinkShown;											 // 279
		bool allowSkip;												 // 27A
		bool debounceMainListPress;									 // 27B
		bool nativeConsolePanelIsOpen;								 // 27C
		bool shouldDebounceMainListPress;							 // 27D
		BSScaleformExternalTexture gamerIconTexture;				 // 280
		std::array<BSScaleformExternalTexture, 14> dlcImageTextures; // 298
	};
	static_assert(sizeof(MainMenu) == 0x3E8);
}
