#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/H/HUDPerkVaultBoySwfDisplayEvent.hpp"
#include "RE/S/ShowingDialogueSpeechChallengeAnim.hpp"
#include "RE/S/ShowingPerkVaultBoyState.hpp"
#include "RE/S/ShowingVATSCritAnim.hpp"

namespace RE
{
	class HUDPerkVaultBoyData;

	class __declspec(novtable) HUDPerkVaultBoyModel
		: public BSTEventSink<HUDPerkVaultBoyData> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDPerkVaultBoyModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDPerkVaultBoyModel };

		~HUDPerkVaultBoyModel() override; // 00

		// override (BSTEventSink<HUDPerkVaultBoyData>)
		BSEventNotifyControl ProcessEvent(const HUDPerkVaultBoyData& a_event, BSTEventSource<HUDPerkVaultBoyData>* a_eventSource) override; // 01

		// members
		BSTObjectArena<HUDPerkVaultBoyData, BSTObjectArenaHeapAlloc, 32> displayDataArray; // 08
		BSTValueEventSource<HUDPerkVaultBoySwfDisplayEvent> currentPerkVaultBoy;		   // 40
		BSTValueEventSink<ShowingPerkVaultBoyState> hudShowingVaultBoy;					   // 70
		BSTValueEventSink<ShowingVATSCritAnim> vatsShowingAnim;							   // 88
		BSTValueEventSink<ShowingDialogueSpeechChallengeAnim> showingSpeechChallenge;	   // A0
		CountdownTimer cooldownTimer;													   // B8
		mutable BSSpinLock dataLock;													   // D0
	};
	static_assert(sizeof(HUDPerkVaultBoyModel) == 0xD8);
}
