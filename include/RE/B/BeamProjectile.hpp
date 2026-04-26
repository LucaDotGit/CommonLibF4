#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/Projectile.hpp"
#include "RE/P/ProjectileLaunchData.hpp"

namespace RE
{
	class BeamProjectileImpactEvent;
	class bhkCollisionQueryResultHandle;
	class BSProceduralGeomEvent;

	class __declspec(novtable) BeamProjectile
		: public Projectile,								// 000
		  public BSTEventSource<BeamProjectileImpactEvent>, // 278
		  public BSTEventSink<BSProceduralGeomEvent>		// 270
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BeamProjectile };
		inline static constexpr auto VTABLE{ VTABLE::BeamProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kBeamProjectile };

		// members
		ProjectileLaunchData launchData;		   // 2D0
		bhkCollisionQueryResultHandle* castResult; // 370
		REX::Float32 baseModelLength;			   // 378
		bool transformSet;						   // 37C
		bool queueUncull;						   // 37D
		bool dealtDamage;						   // 37E
	};
	static_assert(sizeof(BeamProjectile) == 0x380);
}
