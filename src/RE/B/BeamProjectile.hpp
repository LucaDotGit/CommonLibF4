#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/Projectile.hpp"
#include "RE/P/ProjectileLaunchData.hpp"

namespace RE
{
	class BeamProjectileImpactEvent;
	class bhkCollisionQueryResultHandle;
	class BSProceduralGeomEvent;

	class __declspec(novtable) BeamProjectile :
		public Projectile,								  // 0x000
		public BSTEventSource<BeamProjectileImpactEvent>, // 0x278
		public BSTEventSink<BSProceduralGeomEvent>		  // 0x270
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BeamProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::BeamProjectile;
		inline static constexpr auto FORM_TYPE = FormType::BeamProjectile;

		// members
		ProjectileLaunchData launchData;		   // 0x2D0
		bhkCollisionQueryResultHandle* castResult; // 0x370
		REX::Float32 baseModelLength;			   // 0x378
		bool transformSet;						   // 0x37C
		bool queueUncull;						   // 0x37D
		bool dealtDamage;						   // 0x37E
	};

	static_assert(sizeof(BeamProjectile) == 0x380);
}
