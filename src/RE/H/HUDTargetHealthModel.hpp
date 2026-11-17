#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTOptional.hpp"
#include "RE/C/CountdownTimer.hpp"
#include "RE/E/EnemyHealthTargetType.hpp"
#include "RE/H/HUDEnemyHealthDisplayEvent.hpp"
#include "RE/N/nsUIDebug_UIDebugLogger_NoOp.hpp"
#include "RE/P/PlayerActivatePickRefEvent.hpp"
#include "RE/P/PlayerAutoAimActorEvent.hpp"
#include "RE/V/VATSCommandTargetEvent.hpp"
#include "RE/V/VATSForcedEnemyHealthPercentEvent.hpp"

namespace RE
{
	class HUDTargetHealthModel : public nsUIDebug::UIDebugLogger_NoOp // 0x00
	{
	public:
		// members
		BSTValueEventSink<VATSCommandTargetEvent> vatsTargetEvent;					   // 0x00
		BSTValueEventSink<PlayerAutoAimActorEvent> playerAutoAimActor;				   // 0x20
		BSTValueEventSink<PlayerActivatePickRefEvent> playerActivatePickRef;		   // 0x40
		BSTValueEventSink<VATSForcedEnemyHealthPercentEvent> forcedEnemyHealthPercent; // 0x60
		CountdownTimer healthDisplayTimer;											   // 0x80
		BSTOptional<ObjectRefHandle> currentHealthTarget;							   // 0x98
		REX::Enum<EnemyHealthTargetType, std::int32_t> currentTargetType;			   // 0xA0
		BSTValueEventSource<HUDEnemyHealthDisplayEvent> currentEnemyHealthData;		   // 0xA8
	};

	static_assert(sizeof(HUDTargetHealthModel) == 0xD8);
}
