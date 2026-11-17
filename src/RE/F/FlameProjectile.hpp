#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) FlameProjectile : public Projectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FlameProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::FlameProjectile;
		inline static constexpr auto FORM_TYPE = FormType::FlameProjectile;

		// members
		REX::Float32 expirationTimer; // 0x270
		REX::Float32 coneAngle;		  // 0x274
	};

	static_assert(sizeof(FlameProjectile) == 0x280);
}
