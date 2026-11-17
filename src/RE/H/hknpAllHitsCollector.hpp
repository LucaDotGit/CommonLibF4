#pragma once

#include "RE/H/hkInplaceArray.hpp"
#include "RE/H/hknpCollisionQueryCollector.hpp"
#include "RE/H/hknpCollisionResult.hpp"

namespace RE
{
	class __declspec(novtable) hknpAllHitsCollector : public hknpCollisionQueryCollector // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpAllHitsCollector;
		inline static constexpr const auto& VTABLE = VTABLE::hknpAllHitsCollector;

		~hknpAllHitsCollector() override; // 0x00

		// override (hknpCollisionQueryCollector)
		void Reset() override;										 // 0x01
		void AddHit(const hknpCollisionResult& a_hit) override;		 // 0x02
		auto HasHit() const -> bool override;						 // 0x03
		auto GetNumHits() const -> std::int32_t override;			 // 0x04
		auto GetHits() const -> const hknpCollisionResult* override; // 0x05

		// members
		hkInplaceArray<hknpCollisionResult, 10> hits; // 0x020
	};

	static_assert(sizeof(hknpAllHitsCollector) == 0x3F0);
}
