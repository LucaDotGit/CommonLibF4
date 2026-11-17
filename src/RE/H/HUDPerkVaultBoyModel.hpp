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

	class __declspec(novtable) HUDPerkVaultBoyModel : public BSTEventSink<HUDPerkVaultBoyData> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDPerkVaultBoyModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDPerkVaultBoyModel;

		~HUDPerkVaultBoyModel() override; // 0x00

		// override (BSTEventSink<HUDPerkVaultBoyData>)
		auto ProcessEvent(
			const HUDPerkVaultBoyData& a_event,
			BSTEventSource<HUDPerkVaultBoyData>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// members
		BSTHeapObjectArena<HUDPerkVaultBoyData, 0x20> displayDataArray;				  // 0x08
		BSTValueEventSource<HUDPerkVaultBoySwfDisplayEvent> currentPerkVaultBoy;	  // 0x40
		BSTValueEventSink<ShowingPerkVaultBoyState> hudShowingVaultBoy;				  // 0x70
		BSTValueEventSink<ShowingVATSCritAnim> vatsShowingAnim;						  // 0x88
		BSTValueEventSink<ShowingDialogueSpeechChallengeAnim> showingSpeechChallenge; // 0xA0
		CountdownTimer cooldownTimer;												  // 0xB8
		mutable BSSpinLock dataLock;												  // 0xD0
	};

	static_assert(sizeof(HUDPerkVaultBoyModel) == 0xD8);
}
