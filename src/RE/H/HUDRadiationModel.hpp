#pragma once

#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSString.hpp"
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

	class __declspec(novtable) HUDRadiationModel :
		public BSTEventSink<PlayerActiveEffectChanged::Event>, // 0x000
		public BSTEventSink<EndLoadGameEvent>,				   // 0x008
		public nsUIDebug::UIDebugLogger_NoOp				   // 0x010
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDRadiationModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDRadiationModel;

		~HUDRadiationModel() override; // 0x00

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		auto ProcessEvent(
			const PlayerActiveEffectChanged::Event& a_event,
			BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<EndLoadGameEvent>)
		auto ProcessEvent(
			const EndLoadGameEvent& a_event,
			BSTEventSource<EndLoadGameEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// members
		BSStaticString<22> currentRadiationSoundString;										// 0x010
		BSTSmallArray<REX::Float32, 26> radSoundTierThresholds;								// 0x038
		BSTValueEventSource<CurrentRadsDisplayMagnitude> perFrameRadsDosage;				// 0x0B0
		BSTValueEventSource<CurrentRadsPercentOfLethal> currentPlayerRadsPercent;			// 0x0C8
		BSTValueEventSource<CurrentRadiationSourceCount> environmentalRadiationSourceCount; // 0x0E0
		BSTSmallArray<PlayerRadiationDamageData, 16> environmentalDamageA;					// 0x0F8
		BSTSmallArray<PlayerRadiationDamageData, 16> ingestionDamageA;						// 0x188
		CountdownTimer radsSoundTimer;														// 0x218
		CountdownTimer radWarningDisplayTimer;												// 0x230
		CountdownTimer ingestionRadiationTimer;												// 0x248
		BSSoundHandle radsSoundHandle;														// 0x260
		std::uint32_t currSoundTier;														// 0x268
		mutable BSSpinLock radiationDamageArrayLock;										// 0x27C
	};

	static_assert(sizeof(HUDRadiationModel) == 0x278);
}
