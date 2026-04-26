#pragma once

#include "RE/I/IMovementState.hpp"

namespace RE
{
	enum class ACTOR_LIFE_STATE : std::uint32_t;
	enum class ACTOR_STANCE : std::uint32_t;
	enum class ATTACK_STATE_ENUM : std::uint32_t;
	enum class FLY_STATE : std::uint32_t;
	enum class GUN_STATE : std::uint32_t;
	enum class INTERACTING_STATE : std::uint32_t;
	enum class KNOCK_STATE_ENUM : std::uint32_t;
	enum class RECOIL_ENUM : std::uint32_t;
	enum class SIT_SLEEP_STATE : std::uint32_t;
	enum class WEAPON_STATE : std::uint32_t;

	class __declspec(novtable) ActorState
		: public IMovementState // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActorState };
		inline static constexpr auto VTABLE{ VTABLE::ActorState };

		~ActorState() override; // 00

		// add
		virtual bool SetWeaponMagicDrawn(bool a_drawn);				  // 21
		virtual bool SetWeaponState(WEAPON_STATE a_state);			  // 22
		virtual bool DoSetSitSleepState(SIT_SLEEP_STATE a_state) = 0; // 23
		virtual SIT_SLEEP_STATE DoGetSitSleepState() const = 0;		  // 24
		virtual bool SetInIronSightsImpl(bool a_sighted) = 0;		  // 25
		virtual void SetReloadingImpl(bool a_reloading);			  // 26

		// members
		std::uint32_t movingBack		   : 1; // 0:00
		std::uint32_t movingForward		   : 1; // 0:01
		std::uint32_t movingRight		   : 1; // 0:02
		std::uint32_t movingLeft		   : 1; // 0:03
		std::uint32_t unk04				   : 1; // 0:04
		std::uint32_t walking			   : 1; // 0:05
		std::uint32_t running			   : 1; // 0:06
		std::uint32_t sprinting			   : 1; // 0:07
		std::uint32_t sneaking			   : 1; // 0:08
		std::uint32_t swimming			   : 1; // 0:09
		SIT_SLEEP_STATE sitSleepState	   : 4; // 08:10
		FLY_STATE flyState				   : 3; // 08:14
		ACTOR_LIFE_STATE lifeState		   : 4; // 08:17
		KNOCK_STATE_ENUM knockState		   : 4; // 08:21
		ATTACK_STATE_ENUM attackState	   : 3; // 08:25
		std::uint32_t talkingToPlayer	   : 1; // 08:28
		std::uint32_t forceRun			   : 1; // 08:29
		std::uint32_t forceSneak		   : 1; // 08:30
		std::uint32_t headTracking		   : 1; // 08:31
		std::uint32_t reanimating		   : 1; // 0C:00
		WEAPON_STATE weaponState		   : 3; // 0C:01
		std::uint32_t wantBlocking		   : 1; // 0C:04
		std::uint32_t flightBlocked		   : 1; // 0C:05
		RECOIL_ENUM recoilState			   : 2; // 0C:06
		std::uint32_t allowFlying		   : 1; // 0C:08
		std::uint32_t staggered			   : 1; // 0C:09
		std::uint32_t inWrongProcessLevel  : 1; // 0C:10
		ACTOR_STANCE stance				   : 3; // 0C:11
		GUN_STATE gunState				   : 4; // 0C:14
		INTERACTING_STATE interactingState : 2; // 0C:18
		std::uint32_t headTrackRotation	   : 1; // 0C:20
		std::uint32_t inSyncAnim		   : 1; // 0C:21
	};
	static_assert(sizeof(ActorState) == 0x10);
}
