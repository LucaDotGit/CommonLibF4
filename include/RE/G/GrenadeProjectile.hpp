#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) GrenadeProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GrenadeProjectile };
		inline static constexpr auto VTABLE{ VTABLE::GrenadeProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kGrenadeProjectile };

		// members
		BGSDecalGroup* decalGroup; // 270
		bool collisionGroupReset;  // 278
	};
	static_assert(sizeof(GrenadeProjectile) == 0x280);
}
