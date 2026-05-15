#pragma once

#include "RE/H/hknpShape.hpp"
#include "RE/H/hknpSparseCompactMap.hpp"

namespace RE
{
	class __declspec(novtable) hknpCompositeShape
		: public hknpShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpCompositeShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpCompositeShape };

		~hknpCompositeShape() override; // 00

		// members
		hknpSparseCompactMap<std::uint16_t> edgeWeldingMap; // 30
		std::uint32_t shapeTagCodecInfo;					// 58
	};
	static_assert(sizeof(hknpCompositeShape) == 0x60);
}
