#pragma once

#include "RE/A/ActionPoints.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/H/HitData.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BGSBodyPartDefs
{
	enum class LIMB_ENUM : std::int32_t;
}

namespace RE
{
	class SpellItem;

	class VATSCommand
		: public BSIntrusiveRefCounted // 000
	{
	public:
		// members
		ActionPoints::Action action;							  // 004
		ObjectRefHandle target;									  // 008
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limb; // 00C
		NiPointer<NiAVObject> aimAtObj;							  // 010
		HitData hitData;										  // 020
		SpellItem* meleeImpactEffect;							  // 100
		REX::Float32 actionPointCost;							  // 108
		REX::Float32 minActionTime;								  // 10C
		REX::Float32 actionExecuteDelay;						  // 110
		REX::Float32 fakeShotFrequency;							  // 114
		REX::Float32 damageMult;								  // 118
		std::uint32_t loadedAmmoCount;							  // 11C
		std::uint8_t fireShots;									  // 120
		struct
		{
			std::uint8_t stranger				: 1;
			std::uint8_t paralyzingPalm			: 1;
			std::uint8_t leftHandCast			: 1;
			std::uint8_t executeAction			: 1;
			std::uint8_t actionExecuteSuccess	: 1;
			std::uint8_t nextShotCausesCritical : 1;
			std::uint8_t spendCriticalCharge	: 1;
			std::uint8_t attackChanceHit		: 1;
		} flags01; // 121
		struct
		{
			std::uint8_t shotFired		  : 1;
			std::uint8_t criticalAttack	  : 1;
			std::uint8_t syncedAnim		  : 1;
			std::uint8_t attemptChain	  : 1;
			std::uint8_t allowWarp		  : 1;
			std::uint8_t meleeSneakAttack : 1;
		} flags02; // 122
	};
	static_assert(sizeof(VATSCommand) == 0x130);
}
