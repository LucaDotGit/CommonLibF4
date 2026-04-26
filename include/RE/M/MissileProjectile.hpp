#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/P/Projectile.hpp"

namespace RE
{
	enum class ImpactResult : std::int32_t;

	class bhkNPCollisionObject;

	class __declspec(novtable) MissileProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MissileProjectile };
		inline static constexpr auto VTABLE{ VTABLE::MissileProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kMissileProjectile };

		// add
		virtual bool ShouldReorient() const; // EA

		// members
		NiMatrix3 dismemberedLimbRotation;					// 270
		NiPoint3 dismemberedLimbOffset;						// 2A0
		NiPointer<bhkNPCollisionObject> modelCollision;		// 2B0
		REX::Enum<ImpactResult, std::int32_t> impactResult; // 2B8
		bool waitingToInitialize3D;							// 2BC
		bool deferProcessImpale;							// 2BD
	};
	static_assert(sizeof(MissileProjectile) == 0x2C0);
}
