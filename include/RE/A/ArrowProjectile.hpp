#pragma once

#include "RE/M/MissileProjectile.hpp"

namespace RE
{
	class __declspec(novtable) ArrowProjectile
		: public MissileProjectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ArrowProjectile };
		inline static constexpr auto VTABLE{ VTABLE::ArrowProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kArrowProjectile };

		// members
		AlchemyItem* poison; // 2C0
	};
	static_assert(sizeof(ArrowProjectile) == 0x2D0);
}
