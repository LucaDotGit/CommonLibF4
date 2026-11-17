#pragma once

#include "RE/M/MissileProjectile.hpp"

namespace RE
{
	class __declspec(novtable) ArrowProjectile : public MissileProjectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ArrowProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::ArrowProjectile;
		inline static constexpr auto FORM_TYPE = FormType::ArrowProjectile;

		// members
		AlchemyItem* poison; // 0x2C0
	};

	static_assert(sizeof(ArrowProjectile) == 0x2D0);
}
