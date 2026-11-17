#pragma once

#include "RE/H/hkVector4.hpp"
#include "RE/H/hknpUniqueBodyIdHitCollector.hpp"

namespace RE
{
	class __declspec(novtable) hknpClosestUniqueBodyIdHitCollector : public hknpUniqueBodyIdHitCollector // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpClosestUniqueBodyIdHitCollector;
		inline static constexpr const auto& VTABLE = VTABLE::hknpClosestUniqueBodyIdHitCollector;

		~hknpClosestUniqueBodyIdHitCollector() override; // 0x00

		// members
		hkVector4 center; // 0x400
	};

	static_assert(sizeof(hknpClosestUniqueBodyIdHitCollector) == 0x410);
}
