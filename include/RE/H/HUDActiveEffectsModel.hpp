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

	class __declspec(novtable) HUDActiveEffectsModel
		: public BSTEventSink<PlayerActiveEffectChanged::Event>, // 00
		  public BSTEventSink<EndLoadGameEvent>,				 // 08
		  public nsUIDebug::UIDebugLogger_NoOp					 // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDActiveEffectsModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDActiveEffectsModel };

		~HUDActiveEffectsModel() override;

		// override (BSTEventSink<PlayerActiveEffectChanged::Event>)
		BSEventNotifyControl ProcessEvent(const PlayerActiveEffectChanged::Event& a_event, BSTEventSource<PlayerActiveEffectChanged::Event>* a_eventSource) override; // 01

		// override (BSTEventSink<EndLoadGameEvent>)
		BSEventNotifyControl ProcessEvent(const EndLoadGameEvent& a_event, BSTEventSource<EndLoadGameEvent>* a_eventSource) override; // 01

		// members
		BSTSmallArray<PlayerActiveEffectData, 64> playerActiveEffects;				// 018
		mutable BSSpinLock playerActiveEffectsLock;									// 420
		BSTValueEventSource<PlayerActiveEffectIconsEvent> CurrentActiveEffectIcons; // 428
	};
	static_assert(sizeof(HUDActiveEffectsModel) == 0x460);
}
