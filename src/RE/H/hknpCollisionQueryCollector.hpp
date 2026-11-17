#pragma once

#include "RE/H/hkBaseObject.hpp"
#include "RE/H/hkSimdFloat32.hpp"

namespace RE
{
	class hknpCollisionResult;

	class __declspec(novtable) hknpCollisionQueryCollector : public hkBaseObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCollisionQueryCollector;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCollisionQueryCollector;

		~hknpCollisionQueryCollector() override; // 0x00

		// add
		virtual void Reset() = 0;										// 0x01
		virtual void AddHit(const hknpCollisionResult& a_hit) = 0;		// 0x02
		virtual auto HasHit() const -> bool = 0;						// 0x03
		virtual auto GetNumHits() const -> std::int32_t = 0;			// 0x04
		virtual auto GetHits() const -> const hknpCollisionResult* = 0; // 0x05

		// members
		std::int32_t hints;				 // 0x08
		hkSimdFloat32 earlyOutThreshold; // 0x10
	};

	static_assert(sizeof(hknpCollisionQueryCollector) == 0x20);
}
