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
	class HUDTargetHealthModel
		: public nsUIDebug::UIDebugLogger_NoOp // 00
	{
	public:
		// members
		BSTValueEventSink<VATSCommandTargetEvent> vatsTargetEvent;					   // 00
		BSTValueEventSink<PlayerAutoAimActorEvent> playerAutoAimActor;				   // 20
		BSTValueEventSink<PlayerActivatePickRefEvent> playerActivatePickRef;		   // 40
		BSTValueEventSink<VATSForcedEnemyHealthPercentEvent> forcedEnemyHealthPercent; // 60
		CountdownTimer healthDisplayTimer;											   // 80
		BSTOptional<ObjectRefHandle> currentHealthTarget;							   // 98
		REX::Enum<EnemyHealthTargetType, std::int32_t> currentTargetType;			   // A0
		BSTValueEventSource<HUDEnemyHealthDisplayEvent> currentEnemyHealthData;		   // A8
	};
	static_assert(sizeof(HUDTargetHealthModel) == 0xD8);
}
