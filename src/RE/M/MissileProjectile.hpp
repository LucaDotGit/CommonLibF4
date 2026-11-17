#pragma once

#include "RE/N/NiMatrix3.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/P/Projectile.hpp"

namespace RE
{
	enum class ImpactResult : std::int32_t;

	class bhkNPCollisionObject;

	class __declspec(novtable) MissileProjectile : public Projectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::MissileProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::MissileProjectile;
		inline static constexpr auto FORM_TYPE = FormType::MissileProjectile;

		// add
		virtual auto ShouldReorient() const -> bool; // 0xEA

		// members
		NiMatrix3 dismemberedLimbRotation;					// 0x270
		NiPoint3 dismemberedLimbOffset;						// 0x2A0
		NiPointer<bhkNPCollisionObject> modelCollision;		// 0x2B0
		REX::Enum<ImpactResult, std::int32_t> impactResult; // 0x2B8
		bool waitingToInitialize3D;							// 0x2BC
		bool deferProcessImpale;							// 0x2BD
	};

	static_assert(sizeof(MissileProjectile) == 0x2C0);
}
