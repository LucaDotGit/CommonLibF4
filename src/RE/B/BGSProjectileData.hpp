#pragma once

namespace RE
{
	class BGSProjectileData
	{
	public:
		enum class Flags : std::uint16_t
		{
			None = 0,
			HitScan = 1 << 0,
			Explosion = 1 << 1,
			ExplosionAltTrigger = 1 << 2,
			MuzzleFlash = 1 << 3,
			CanTurnOff = 1 << 5,
			CanPickUp = 1 << 6,
			Supersonic = 1 << 7,
			PinsLimbs = 1 << 8,
			PassSmallTransparent = 1 << 9,
			DisableCombatAimCorrection = 1 << 10,
			PenetratesGeometry = 1 << 11,
			ContinuousUpdate = 1 << 12,
			SeeksTarget = 1 << 13
		};

		enum class Type : std::int16_t
		{
			None = 0,
			Missile = 1 << 0,
			Lobber = 1 << 1,
			Beam = 1 << 2,
			Flame = 1 << 3,
			Cone = 1 << 4,
			Barrier = 1 << 5,
			Arrow = 1 << 6
		};

		// members
		REX::EnumSet<Flags, std::uint16_t> flags; // 0x00
		REX::Enum<Type, std::int16_t> type;		  // 0x02
		REX::Float32 gravity;					  // 0x04
		REX::Float32 speed;						  // 0x08
		REX::Float32 range;						  // 0x0C
		TESObjectLIGH* light;					  // 0x10
		TESObjectLIGH* muzzleFlashLight;		  // 0x18
		REX::Float32 explosionProximity;		  // 0x20
		REX::Float32 explosionTimer;			  // 0x24
		BGSExplosion* explosionType;			  // 0x28
		BGSSoundDescriptorForm* activeSoundLoop;  // 0x30
		REX::Float32 muzzleFlashDuration;		  // 0x38
		REX::Float32 fadeOutTime;				  // 0x3C
		REX::Float32 force;						  // 0x40
		BGSSoundDescriptorForm* countdownSound;	  // 0x48
		BGSSoundDescriptorForm* deactivateSound;  // 0x50
		TESObjectWEAP* defaultWeaponSource;		  // 0x58
		REX::Float32 coneSpread;				  // 0x60
		REX::Float32 collisionRadius;			  // 0x64
		REX::Float32 lifetime;					  // 0x68
		REX::Float32 relaunchInterval;			  // 0x6C
		BGSTextureSet* decalData;				  // 0x70
		BGSCollisionLayer* collisionLayer;		  // 0x78
		BGSProjectile* vatsProjectile;			  // 0x80
		std::int8_t tracerFrequency;			  // 0x88
	};

	static_assert(sizeof(BGSProjectileData) == 0x90);
}
