#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/H/HUDPerkVaultBoySwfDisplayEvent.hpp"
#include "RE/S/ShowingDialogueSpeechChallengeAnim.hpp"
#include "RE/U/UI_DEPTH_PRIORITY.hpp"
#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) DialogueMenu : public GameMenuBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::DialogueMenu;
		inline static constexpr const auto& VTABLE = VTABLE::DialogueMenu;
		inline static constexpr auto MENU_NAME = "DialogueMenu"sv;
		inline static constexpr auto MENU_DEPTH = UI_DEPTH_PRIORITY::DialogueMenu;

		~DialogueMenu() override; // 0x00

		// members
		std::array<msvc::unique_ptr<BSGFxShaderFXTarget>, 4> dialogueButtonObjs;		// 0x0E0
		msvc::unique_ptr<BSGFxShaderFXTarget> speechChallengeAnimObj;					// 0x100
		BSTValueEventSink<HUDPerkVaultBoySwfDisplayEvent> currentVBPerk;				// 0x108
		BSTValueEventSource<ShowingDialogueSpeechChallengeAnim> showingSpeechChallenge; // 0x140
		BSTSmartPointer<BSInputEnableLayer> inputLayer;									// 0x158
		UserEvents::INPUT_CONTEXT_ID currentContext;									// 0x160
		bool isLookingAtPlayer;															// 0x164
		bool areButtonsShown;															// 0x165
	};

	static_assert(sizeof(DialogueMenu) == 0x168);
}
