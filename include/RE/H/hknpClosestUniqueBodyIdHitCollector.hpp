#pragma once

#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpUniqueBodyIdHitCollector.hpp"

namespace RE
{
	class __declspec(novtable) hknpClosestUniqueBodyIdHitCollector
		: public hknpUniqueBodyIdHitCollector // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpClosestUniqueBodyIdHitCollector };
		inline static constexpr auto VTABLE{ VTABLE::hknpClosestUniqueBodyIdHitCollector };

		~hknpClosestUniqueBodyIdHitCollector() override; // 00

		// members
		hkVector4 center; // 400
	};
	static_assert(sizeof(hknpClosestUniqueBodyIdHitCollector) == 0x410);
}
