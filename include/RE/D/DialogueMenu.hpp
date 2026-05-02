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
		std::array<msvc::unique_ptr<BSGFxShaderFXTarget>, 4> dialogueButtonObjs;		// 0E0
		msvc::unique_ptr<BSGFxShaderFXTarget> speechChallengeAnimObj;					// 100
		BSTValueEventSink<HUDPerkVaultBoySwfDisplayEvent> currentVBPerk;				// 108
		BSTValueEventSource<ShowingDialogueSpeechChallengeAnim> showingSpeechChallenge; // 140
		BSTSmartPointer<BSInputEnableLayer> inputLayer;									// 158
		UserEvents::INPUT_CONTEXT_ID currentContext;									// 160
		bool isLookingAtPlayer;															// 164
		bool areButtonsShown;															// 165
	};
	static_assert(sizeof(DialogueMenu) == 0x168);
}
