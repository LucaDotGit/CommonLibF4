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

	class VATSCommand : public BSIntrusiveRefCounted // 0x000
	{
	public:
		// members
		ActionPoints::Action action;							  // 0x004
		ObjectRefHandle target;									  // 0x008
		REX::Enum<BGSBodyPartDefs::LIMB_ENUM, std::int32_t> limb; // 0x00C
		NiPointer<NiAVObject> aimAtObj;							  // 0x010
		HitData hitData;										  // 0x020
		SpellItem* meleeImpactEffect;							  // 0x100
		REX::Float32 actionPointCost;							  // 0x108
		REX::Float32 minActionTime;								  // 0x10C
		REX::Float32 actionExecuteDelay;						  // 0x110
		REX::Float32 fakeShotFrequency;							  // 0x114
		REX::Float32 damageMult;								  // 0x118
		std::uint32_t loadedAmmoCount;							  // 0x11C
		std::uint8_t fireShots;									  // 0x120

		struct
		{
		public:
			// members
			std::uint8_t stranger				: 1; // 0x121:00
			std::uint8_t paralyzingPalm			: 1; // 0x121:01
			std::uint8_t leftHandCast			: 1; // 0x121:02
			std::uint8_t executeAction			: 1; // 0x121:03
			std::uint8_t actionExecuteSuccess	: 1; // 0x121:04
			std::uint8_t nextShotCausesCritical : 1; // 0x121:05
			std::uint8_t spendCriticalCharge	: 1; // 0x121:06
			std::uint8_t attackChanceHit		: 1; // 0x121:07
		} flags01;									 // 0x121

		struct
		{
		public:
			// members
			std::uint8_t shotFired		  : 1; // 0x122:00
			std::uint8_t criticalAttack	  : 1; // 0x122:01
			std::uint8_t syncedAnim		  : 1; // 0x122:02
			std::uint8_t attemptChain	  : 1; // 0x122:03
			std::uint8_t allowWarp		  : 1; // 0x122:04
			std::uint8_t meleeSneakAttack : 1; // 0x122:05
		} flags02;							   // 0x122
	};

	static_assert(sizeof(VATSCommand) == 0x130);
}
