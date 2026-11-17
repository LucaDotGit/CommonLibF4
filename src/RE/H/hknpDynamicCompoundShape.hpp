#pragma once

#include "RE/H/hknpCompoundShape.hpp"

namespace RE
{
	class hknpDynamicCompoundShapeData;

	class __declspec(novtable) hknpDynamicCompoundShape : public hknpCompoundShape // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::hknpDynamicCompoundShape;
		inline static constexpr const auto& VTABLE = VTABLE::hknpDynamicCompoundShape;

		~hknpDynamicCompoundShape() override; // 0x00

		// members
		hknpDynamicCompoundShapeData* boundingVolumeData; // 0xC0
	};

	static_assert(sizeof(hknpDynamicCompoundShape) == 0xD0);
}
