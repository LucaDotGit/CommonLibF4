#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/P/Projectile.hpp"

namespace RE
{
	class __declspec(novtable) BarrierProjectile : public Projectile // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BarrierProjectile;
		inline static constexpr const auto& VTABLE = VTABLE::BarrierProjectile;
		inline static constexpr auto FORM_TYPE = FormType::BarrierProjectile;

		class CollisionData
		{
		public:
			// members
			ObjectRefHandle ref; // 0x00
			std::uint32_t count; // 0x04
		};

		static_assert(sizeof(CollisionData) == 0x08);

		// members
		REX::Float32 width;							// 0x270
		BSTArray<CollisionData> collisionDataArray; // 0x278
	};

	static_assert(sizeof(BarrierProjectile) == 0x290);
}
