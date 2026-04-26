#pragma once

#include "RE/R/Rumble.hpp"
#include "RE/S/StartMenuBase.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) PauseMenu
		: public StartMenuBase // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PauseMenu };
		inline static constexpr auto VTABLE{ VTABLE::PauseMenu };
		inline static constexpr auto MENU_NAME{ "PauseMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kPauseMenu };

		~PauseMenu() override; // 00

		// members
		msvc::unique_ptr<BSGFxShaderFXTarget> helpTopicList;	 // 228
		msvc::unique_ptr<BSGFxShaderFXTarget> helpPanelBrackets; // 230
		msvc::unique_ptr<BSGFxShaderFXTarget> helpListBrackets;	 // 238
		msvc::unique_ptr<BSGFxShaderFXTarget> helpText;			 // 240
		msvc::unique_ptr<BSGFxShaderFXTarget> helpTitleText;	 // 248
		msvc::unique_ptr<BSGFxShaderFXTarget> helpScrollUp;		 // 250
		msvc::unique_ptr<BSGFxShaderFXTarget> helpScrollDown;	 // 258
		Rumble::AutoRumblePause rumbleLock;						 // 260
		bool hideScreen3D;										 // 261
		bool modMenuShaderWasEnabled;							 // 262
		bool vatsWasEnabled;									 // 263
		bool vatsDepthTestMask;									 // 264
		bool quitToMainMenuQueued;								 // 265
		bool quitToDesktopQueued;								 // 266
		bool noProfileSelected;									 // 267
	};
	static_assert(sizeof(PauseMenu) == 0x268);
}
