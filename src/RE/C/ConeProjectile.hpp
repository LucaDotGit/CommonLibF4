#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) ConeProjectile : public Projectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ConeProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::ConeProjectile;
		inline static constexpr auto FORM_TYPE = FormType::ConeProjectile;

		// members
		REX::Float32 expirationTimer; // 0x270
		REX::Float32 coneAngle;		  // 0x274
	};

	static_assert(sizeof(ConeProjectile) == 0x280);
}
