#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/H/HeldStateHandler.hpp"
#include "RE/S/SettingT.hpp"

namespace RE
{
	class INISettingCollection;

	class __declspec(novtable) AttackBlockHandler
		: public HeldStateHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AttackBlockHandler };
		inline static constexpr auto VTABLE{ VTABLE::AttackBlockHandler };

		enum class POWER_ATTACK_STATE : std::int32_t
		{
			kNone = 0,
			kLeft = 1,
			kRight = 2,
			kDual = 3
		};

		// members
		std::uint64_t dualAttackStartTime;								  // 28
		BSFixedString debounceEvent;									  // 30
		REX::Enum<POWER_ATTACK_STATE, std::uint32_t> checkForPowerAttack; // 38
		std::uint32_t numPowerAttacks;									  // 3C
		SettingT<INISettingCollection>* initialDelay;					  // 40
		SettingT<INISettingCollection>* subsequentDelay;				  // 48
		REX::Float32 attackTimer;										  // 50
		std::uint64_t rightAttackTimestamp;								  // 58
		REX::Float32 rightAttackHeldSeconds;							  // 60
		REX::Float32 rightAttackLastHeldSeconds;						  // 64
		REX::Float32 rightAttackLatchEngage;							  // 68
		REX::Float32 rightAttackLatchRelease;							  // 6C
		bool debounce;													  // 70
		bool castAttemptMade;											  // 71
		bool leftAttackButtonHeld;										  // 72
		bool rightAttackButtonHeld;										  // 73
		bool rightAttackQueued;											  // 74
		bool rightAttackPrevFrame;										  // 75
		bool setAttackTimer;											  // 76
		bool checkPostMeleeActions;										  // 77
		bool checkPostThrowActions;										  // 78
	};
	static_assert(sizeof(AttackBlockHandler) == 0x80);
}
