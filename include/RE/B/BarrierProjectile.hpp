#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) BarrierProjectile
		: public Projectile // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BarrierProjectile };
		inline static constexpr auto VTABLE{ VTABLE::BarrierProjectile };
		inline static constexpr auto FORM_TYPE{ FormType::kBarrierProjectile };

		class CollisionData
		{
		public:
			// members
			ObjectRefHandle ref; // 00
			std::uint32_t count; // 04
		};
		static_assert(sizeof(CollisionData) == 0x08);

		// members
		REX::Float32 width;							// 270
		BSTArray<CollisionData> collisionDataArray; // 278
	};
	static_assert(sizeof(BarrierProjectile) == 0x290);
}
