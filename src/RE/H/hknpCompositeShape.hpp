#pragma once

#include "RE/H/hknpShape.hpp"
#include "RE/H/hknpSparseCompactMap.hpp"

namespace RE
{
	class __declspec(novtable) hknpCompositeShape : public hknpShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpCompositeShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpCompositeShape;

		~hknpCompositeShape() override; // 0x00

		// members
		hknpSparseCompactMap<std::uint16_t> edgeWeldingMap; // 0x30
		std::uint32_t shapeTagCodecInfo;					// 0x58
	};

	static_assert(sizeof(hknpCompositeShape) == 0x60);
}
