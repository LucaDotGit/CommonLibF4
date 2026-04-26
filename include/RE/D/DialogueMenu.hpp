#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameMenuBase.hpp"
#include "RE/H/HUDPerkVaultBoySwfDisplayEvent.hpp"
#include "RE/S/ShowingDialogueSpeechChallengeAnim.hpp"

#include "msvc/memory.hpp"

namespace RE
{
	class __declspec(novtable) DialogueMenu
		: public GameMenuBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DialogueMenu };
		inline static constexpr auto VTABLE{ VTABLE::DialogueMenu };
		inline static constexpr auto MENU_NAME{ "DialogueMenu"sv };
		inline static constexpr auto MENU_DEPTH{ UI_DEPTH_PRIORITY::kDialogueMenu };

		~DialogueMenu() override; // 00

		// members
		std::array<msvc::unique_ptr<BSGFxShaderFXTarget>, 4> dialogueButtonOBJs;		// 0E0
		msvc::unique_ptr<BSGFxShaderFXTarget> speechChallengeAnimObj;					// 100
		BSTValueEventSink<HUDPerkVaultBoySwfDisplayEvent> CurrentVBPerk;				// 108
		BSTValueEventSource<ShowingDialogueSpeechChallengeAnim> ShowingSpeechChallenge; // 140
		BSTSmartPointer<BSInputEnableLayer> inputLayer;									// 158
		UserEvents::INPUT_CONTEXT_ID CurrentContext;									// 160
		bool IsLookingAtPlayer;															// 164
		bool AreButtonsShown;															// 165
	};
	static_assert(sizeof(DialogueMenu) == 0x168);
}
