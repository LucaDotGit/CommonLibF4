#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/P/PlayerActiveEffectData.hpp"
#include "RE/P/PlayerActiveEffectIconsEvent.hpp"

namespace RE::PlayerActiveEffectChanged
{
	class Event;
}

namespace RE
{
	class EndLoadGameEvent;

	class __declspec(novtable) HUDActiveEffectsModel :
		public BSTEventSink<PlayerActiveEffectChanged::Event>, // 0x00
		public BSTEventSink<EndLoadGameEvent>,				   // 0x08
		public nsUIDebug::UIDebugLogger_NoOp				   // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::HUDActiveEffectsModel;
		inline static constexpr const auto& VTABLE = VTABLE::HUDActiveEffectsModel;

		~HUDActiveEffectsModel() override; // 0x00

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		auto ProcessEvent(
			const PlayerActiveEffectChanged::Event& a_event,
			BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<EndLoadGameEvent>)
		auto ProcessEvent(
			const EndLoadGameEvent& a_event,
			BSTEventSource<EndLoadGameEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// members
		BSTSmallArray<PlayerActiveEffectData, 64> playerActiveEffects;				// 0x018
		mutable BSSpinLock playerActiveEffectsLock;									// 0x420
		BSTValueEventSource<PlayerActiveEffectIconsEvent> CurrentActiveEffectIcons; // 0x428
	};

	static_assert(sizeof(HUDActiveEffectsModel) == 0x460);
}
