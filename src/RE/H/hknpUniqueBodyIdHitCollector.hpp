#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpAllHitsCollector.hpp"

namespace RE
{
	class hknpBSWorld;

	class __declspec(novtable) hknpUniqueBodyIdHitCollector : public hknpAllHitsCollector // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpUniqueBodyIdHitCollector;
		inline static constexpr const auto& VTABLE = VTABLE::hknpUniqueBodyIdHitCollector;

		~hknpUniqueBodyIdHitCollector() override; // 0x00

		// members
		hkRefPtr<hknpBSWorld> latentWorld; // 0x3F0
	};

	static_assert(sizeof(hknpUniqueBodyIdHitCollector) == 0x400);
}
