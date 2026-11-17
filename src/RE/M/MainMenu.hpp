#pragma once

#include "RE/B/BSScaleformExternalTexture.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/S/StartMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"

namespace RE
{
	class MenuOpenCloseEvent;

	class MainMenu :
		public StartMenuBase,					// 0x000
		public BSTEventSink<MenuOpenCloseEvent> // 0x228
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MainMenu;
		inline static constexpr const auto& VTABLE = VTABLE::MainMenu;
		inline static constexpr auto MENU_NAME = "MainMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::MainMenu;

		enum class MAIN_MENU_EXIT_CONDITION : std::int32_t
		{
			NoExit = 0,
			NewGame = 1,
			Continue = 2,
			LoadGame = 3
		};

		~MainMenu() override; // 0x00

		// members
		MAIN_MENU_EXIT_CONDITION mainMenuExitCondition;				 // 0x230
		BSTSet<std::uint32_t> ownedDLC;								 // 0x238
		std::uint64_t creationTime;									 // 0x268
		std::int32_t queuedLoadIndex;								 // 0x270
		bool choseContinue;											 // 0x274
		bool queueStartNewGame;										 // 0x275
		bool queueContinueGame;										 // 0x276
		bool creditScreen;											 // 0x277
		bool userEngaged;											 // 0x278
		bool mainBinkShown;											 // 0x279
		bool allowSkip;												 // 0x27A
		bool debounceMainListPress;									 // 0x27B
		bool nativeConsolePanelIsOpen;								 // 0x27C
		bool shouldDebounceMainListPress;							 // 0x27D
		BSScaleformExternalTexture gamerIconTexture;				 // 0x280
		std::array<BSScaleformExternalTexture, 14> dlcImageTextures; // 0x298
	};

	static_assert(sizeof(MainMenu) == 0x3E8);
}
