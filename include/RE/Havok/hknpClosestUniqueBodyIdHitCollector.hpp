#pragma once

#include "RE/Havok/hkVector4.hpp"
#include "RE/Havok/hknpUniqueBodyIdHitCollector.hpp"

namespace RE
{
	class __declspec(novtable) hknpClosestUniqueBodyIdHitCollector
		: public hknpUniqueBodyIdHitCollector // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpClosestUniqueBodyIdHitCollector };
		inline static constexpr auto VTABLE{ VTABLE::hknpClosestUniqueBodyIdHitCollector };

		// members
		hkVector4f center; // 400
	};
	static_assert(sizeof(hknpClosestUniqueBodyIdHitCollector) == 0x410);
}
