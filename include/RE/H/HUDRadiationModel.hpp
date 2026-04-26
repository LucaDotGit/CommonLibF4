#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/C/CurrentRadiationSourceCount.hpp"
#include "RE/C/CurrentRadsDisplayMagnitude.hpp"
#include "RE/C/CurrentRadsPercentOfLethal.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/P/PlayerRadiationDamageData.hpp"

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE
{
	class EndLoadGameEvent;

	class __declspec(novtable) HUDRadiationModel
		: public BSTEventSink<PlayerActiveEffectChanged::Event>, // 000
		  public BSTEventSink<EndLoadGameEvent>,				 // 008
		  public nsUIDebug::UIDebugLogger_NoOp					 // 010
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDRadiationModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDRadiationModel };

		~HUDRadiationModel() override; // 00

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<EndLoadGameEvent>)
		BSEventNotifyControl ProcessEvent(const EndLoadGameEvent& a_event, BSTEventSource<EndLoadGameEvent>* a_eventSource) override; // 01

		// members
		BSStaticStringT<22> currentRadiationSoundString;									// 010
		BSTSmallArray<REX::Float32, 26> radSoundTierThresholds;								// 038
		BSTValueEventSource<CurrentRadsDisplayMagnitude> perFrameRadsDosage;				// 0B0
		BSTValueEventSource<CurrentRadsPercentOfLethal> currentPlayerRadsPercent;			// 0C8
		BSTValueEventSource<CurrentRadiationSourceCount> environmentalRadiationSourceCount; // 0E0
		BSTSmallArray<PlayerRadiationDamageData, 16> environmentalDamageA;					// 0F8
		BSTSmallArray<PlayerRadiationDamageData, 16> ingestionDamageA;						// 188
		CountdownTimer radsSoundTimer;														// 218
		CountdownTimer radWarningDisplayTimer;												// 230
		CountdownTimer ingestionRadiationTimer;												// 248
		BSSoundHandle radsSoundHandle;														// 260
		std::uint32_t currSoundTier;														// 268
		mutable BSSpinLock radiationDamageArrayLock;										// 27C
	};
	static_assert(sizeof(HUDRadiationModel) == 0x278);
}
