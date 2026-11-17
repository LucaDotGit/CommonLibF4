#pragma once

#include "RE/R/Rumble.hpp"
#include "RE/S/StartMenuBase.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) PauseMenu : public StartMenuBase // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PauseMenu;
		inline static constexpr const auto& VTABLE = VTABLE::PauseMenu;
		inline static constexpr auto MENU_NAME = "PauseMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::PauseMenu;

		~PauseMenu() override; // 0x00

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> helpTopicList;	 // 0x228
		msvc::unique_ptr<BSGFxShaderFXTarget> helpPanelBrackets; // 0x230
		msvc::unique_ptr<BSGFxShaderFXTarget> helpListBrackets;	 // 0x238
		msvc::unique_ptr<BSGFxShaderFXTarget> helpText;			 // 0x240
		msvc::unique_ptr<BSGFxShaderFXTarget> helpTitleText;	 // 0x248
		msvc::unique_ptr<BSGFxShaderFXTarget> helpScrollUp;		 // 0x250
		msvc::unique_ptr<BSGFxShaderFXTarget> helpScrollDown;	 // 0x258
		Rumble::AutoRumblePause rumbleLock;						 // 0x260
		bool hideScreen3D;										 // 0x261
		bool modMenuShaderWasEnabled;							 // 0x262
		bool vatsWasEnabled;									 // 0x263
		bool vatsDepthTestMask;									 // 0x264
		bool quitToMainMenuQueued;								 // 0x265
		bool quitToDesktopQueued;								 // 0x266
		bool noProfileSelected;									 // 0x267
	};

	static_assert(sizeof(PauseMenu) == 0x268);
}
