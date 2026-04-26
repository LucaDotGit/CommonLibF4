#pragma once

#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpAllHitsCollector.hpp"

namespace RE
{
	class hknpBSWorld;

	class __declspec(novtable) hknpUniqueBodyIdHitCollector
		: public hknpAllHitsCollector // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpUniqueBodyIdHitCollector };
		inline static constexpr auto VTABLE{ VTABLE::hknpUniqueBodyIdHitCollector };

		~hknpUniqueBodyIdHitCollector() override; // 00

		// members
		hkRefPtr<hknpBSWorld> latentWorld; // 3F0
	};
	static_assert(sizeof(hknpUniqueBodyIdHitCollector) == 0x400);
}
