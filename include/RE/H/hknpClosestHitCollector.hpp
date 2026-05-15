#pragma once

#include "RE/H/hknpCollisionQueryCollector.hpp"
#include "RE/H/hknpCollisionResult.hpp"

namespace RE
{
	class __declspec(novtable) hknpClosestHitCollector
		: public hknpCollisionQueryCollector // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpClosestHitCollector };
		inline static constexpr auto VTABLE{ VTABLE::hknpClosestHitCollector };

		~hknpClosestHitCollector() override; // 00

		// override (hknpCollisionQueryCollector)
		void Reset() override;									// 01
		void AddHit(const hknpCollisionResult& a_hit) override; // 02
		bool HasHit() const override;							// 03
		std::int32_t GetNumHits() const override;				// 04
		const hknpCollisionResult* GetHits() const override;	// 05

		// members
		hknpCollisionResult result; // 20
		bool hasHit;				// 80
	};
	static_assert(sizeof(hknpClosestHitCollector) == 0x90);
}
