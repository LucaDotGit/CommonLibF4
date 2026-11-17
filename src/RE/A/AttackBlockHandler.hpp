#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/H/HeldStateHandler.hpp"
#include "RE/S/SettingT.hpp"

namespace RE
{
	class INISettingCollection;

	class __declspec(novtable) AttackBlockHandler : public HeldStateHandler // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::AttackBlockHandler;
		inline static constexpr const auto& VTABLE = VTABLE::AttackBlockHandler;

		enum class POWER_ATTACK_STATE : std::int32_t
		{
			None = 0,
			Left = 1,
			Right = 2,
			Dual = 3
		};

		// members
		std::uint64_t dualAttackStartTime;								  // 0x28
		BSFixedString debounceEvent;									  // 0x30
		REX::Enum<POWER_ATTACK_STATE, std::uint32_t> checkForPowerAttack; // 0x38
		std::uint32_t numPowerAttacks;									  // 0x3C
		SettingT<INISettingCollection>* initialDelay;					  // 0x40
		SettingT<INISettingCollection>* subsequentDelay;				  // 0x48
		REX::Float32 attackTimer;										  // 0x50
		std::uint64_t rightAttackTimestamp;								  // 0x58
		REX::Float32 rightAttackHeldSeconds;							  // 0x60
		REX::Float32 rightAttackLastHeldSeconds;						  // 0x64
		REX::Float32 rightAttackLatchEngage;							  // 0x68
		REX::Float32 rightAttackLatchRelease;							  // 0x6C
		bool debounce;													  // 0x70
		bool castAttemptMade;											  // 0x71
		bool leftAttackButtonHeld;										  // 0x72
		bool rightAttackButtonHeld;										  // 0x73
		bool rightAttackQueued;											  // 0x74
		bool rightAttackPrevFrame;										  // 0x75
		bool setAttackTimer;											  // 0x76
		bool checkPostMeleeActions;										  // 0x77
		bool checkPostThrowActions;										  // 0x78
	};

	static_assert(sizeof(AttackBlockHandler) == 0x80);
}
