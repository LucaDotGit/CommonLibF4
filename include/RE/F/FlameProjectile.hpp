#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) FlameProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FlameProjectile };
		inline static constexpr auto VTABLE{ VTABLE::FlameProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kFlameProjectile };

		// members
		REX::Float32 expirationTimer; // 270
		REX::Float32 coneAngle;		  // 274
	};
	static_assert(sizeof(FlameProjectile) == 0x280);
}
