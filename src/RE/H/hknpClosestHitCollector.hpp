#pragma once

#include "RE/H/hknpCollisionQueryCollector.hpp"
#include "RE/H/hknpCollisionResult.hpp"

namespace RE
{
	class __declspec(novtable) hknpClosestHitCollector : public hknpCollisionQueryCollector // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpClosestHitCollector;
		inline static constexpr const auto& VTABLE = VTABLE::hknpClosestHitCollector;

		~hknpClosestHitCollector() override; // 0x00

		// override (hknpCollisionQueryCollector)
		void Reset() override;										 // 0x01
		void AddHit(const hknpCollisionResult& a_hit) override;		 // 0x02
		auto HasHit() const -> bool override;						 // 0x03
		auto GetNumHits() const -> std::int32_t override;			 // 0x04
		auto GetHits() const -> const hknpCollisionResult* override; // 0x05

		// members
		hknpCollisionResult result; // 0x20
		bool hasHit;				// 0x80
	};

	static_assert(sizeof(hknpClosestHitCollector) == 0x90);
}
