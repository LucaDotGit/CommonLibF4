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

#if (_MSC_VER > 0l)
#pragma warning(push)
#pragma warning(disable : 5'249)
#endif

	class __declspec(novtable) ActorState : public IMovementState // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActorState;
		inline static constexpr const auto& VTABLE = VTABLE::ActorState;

		~ActorState() override; // 0x00

		// add
		virtual auto SetWeaponMagicDrawn(bool a_drawn) -> bool;				  // 0x21
		virtual auto SetWeaponState(WEAPON_STATE a_state) -> bool;			  // 0x22
		virtual auto DoSetSitSleepState(SIT_SLEEP_STATE a_state) -> bool = 0; // 0x23
		virtual auto DoGetSitSleepState() const -> SIT_SLEEP_STATE = 0;		  // 0x24
		virtual auto SetInIronSightsImpl(bool a_sighted) -> bool = 0;		  // 0x25
		virtual void SetReloadingImpl(bool a_reloading);					  // 0x26

		// members
		std::uint32_t movingBackward	   : 1; // 0x00:00
		std::uint32_t movingForward		   : 1; // 0x00:01
		std::uint32_t movingRight		   : 1; // 0x00:02
		std::uint32_t movingLeft		   : 1; // 0x00:03
		std::uint32_t jogging			   : 1; // 0x00:04
		std::uint32_t walking			   : 1; // 0x00:05
		std::uint32_t running			   : 1; // 0x00:06
		std::uint32_t sprinting			   : 1; // 0x00:07
		std::uint32_t swimming			   : 1; // 0x00:08
		std::uint32_t sneaking			   : 1; // 0x00:09
		SIT_SLEEP_STATE sitSleepState	   : 4; // 0x08:10
		FLY_STATE flyState				   : 3; // 0x08:14
		ACTOR_LIFE_STATE lifeState		   : 4; // 0x08:17
		KNOCK_STATE_ENUM knockState		   : 4; // 0x08:21
		ATTACK_STATE_ENUM meleeAttackState : 3; // 0x08:25
		std::uint32_t talkingToPlayer	   : 1; // 0x08:28
		std::uint32_t forceRun			   : 1; // 0x08:29
		std::uint32_t forceSneak		   : 1; // 0x08:30
		std::uint32_t headTracking		   : 1; // 0x08:31
		std::uint32_t reanimating		   : 1; // 0x0C:00
		WEAPON_STATE weaponState		   : 3; // 0x0C:01
		std::uint32_t wantBlocking		   : 1; // 0x0C:04
		std::uint32_t flightBlocked		   : 1; // 0x0C:05
		RECOIL_ENUM recoilState			   : 2; // 0x0C:06
		std::uint32_t allowFlying		   : 1; // 0x0C:08
		std::uint32_t staggered			   : 1; // 0x0C:09
		std::uint32_t inWrongProcessLevel  : 1; // 0x0C:10
		ACTOR_STANCE stance				   : 3; // 0x0C:11
		GUN_STATE gunState				   : 4; // 0x0C:14
		INTERACTING_STATE interactingState : 2; // 0x0C:18
		std::uint32_t headTrackRotation	   : 1; // 0x0C:20
		std::uint32_t inSyncAnim		   : 1; // 0x0C:21
	};

	static_assert(sizeof(ActorState) == 0x10);

#if (_MSC_VER > 0l)
#pragma warning(pop)
#endif
}
