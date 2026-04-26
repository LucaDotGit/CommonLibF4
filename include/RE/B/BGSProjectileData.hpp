#pragma once

namespace RE
{
	class BGSProjectileData
	{
	public:
		enum class Flags : std::uint16_t
		{
			kNone = 0,
			kHitScan = 1 << 0,
			kExplosion = 1 << 1,
			kExplosionAltTrigger = 1 << 2,
			kMuzzleFlash = 1 << 3,
			kCanTurnOff = 1 << 5,
			kCanPickUp = 1 << 6,
			kSupersonic = 1 << 7,
			kPinsLimbs = 1 << 8,
			kPassSmallTransparent = 1 << 9,
			kDisableCombatAimCorrection = 1 << 10,
			kPenetratesGeometry = 1 << 11,
			kContinuousUpdate = 1 << 12,
			kSeeksTarget = 1 << 13
		};

		enum class Type : std::int16_t
		{
			kNone = 0,
			kMissile = 1 << 0,
			kLobber = 1 << 1,
			kBeam = 1 << 2,
			kFlame = 1 << 3,
			kCone = 1 << 4,
			kBarrier = 1 << 5,
			kArrow = 1 << 6
		};

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 00
		REX::Enum<Type, std::int16_t> type;		  // 02
		REX::Float32 gravity;					  // 04
		REX::Float32 speed;						  // 08
		REX::Float32 range;						  // 0C
		TESObjectLIGH* light;					  // 10
		TESObjectLIGH* muzzleFlashLight;		  // 18
		REX::Float32 explosionProximity;		  // 20
		REX::Float32 explosionTimer;			  // 24
		BGSExplosion* explosionType;			  // 28
		BGSSoundDescriptorForm* activeSoundLoop;  // 30
		REX::Float32 muzzleFlashDuration;		  // 38
		REX::Float32 fadeOutTime;				  // 3C
		REX::Float32 force;						  // 40
		BGSSoundDescriptorForm* countdownSound;	  // 48
		BGSSoundDescriptorForm* deactivateSound;  // 50
		TESObjectWEAP* defaultWeaponSource;		  // 58
		REX::Float32 coneSpread;				  // 60
		REX::Float32 collisionRadius;			  // 64
		REX::Float32 lifetime;					  // 68
		REX::Float32 relaunchInterval;			  // 6C
		BGSTextureSet* decalData;				  // 70
		BGSCollisionLayer* collisionLayer;		  // 78
		BGSProjectile* vatsProjectile;			  // 80
		std::int8_t tracerFrequency;			  // 88
	};
	static_assert(sizeof(BGSProjectileData) == 0x90);
}
