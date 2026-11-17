#pragma once

#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) GrenadeProjectile : public Projectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GrenadeProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::GrenadeProjectile;
		inline static constexpr auto FORM_TYPE = FormType::GrenadeProjectile;

		// members
		BGSDecalGroup* decalGroup; // 0x270
		bool collisionGroupReset;  // 0x278
	};

	static_assert(sizeof(GrenadeProjectile) == 0x280);
}
