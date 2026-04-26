#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) ConeProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ConeProjectile };
		inline static constexpr auto VTABLE{ VTABLE::ConeProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kConeProjectile };

		// members
		REX::Float32 expirationTimer; // 270
		REX::Float32 coneAngle;		  // 274
	};
	static_assert(sizeof(ConeProjectile) == 0x280);
}
