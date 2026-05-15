#pragma once

#include "RE/H/hknpCompoundShape.hpp"

namespace RE
{
	class hknpDynamicCompoundShapeData;

	class __declspec(novtable) hknpDynamicCompoundShape
		: public hknpCompoundShape // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::hknpDynamicCompoundShape };
		inline static constexpr auto VTABLE{ VTABLE::hknpDynamicCompoundShape };

		~hknpDynamicCompoundShape() override; // 00

		// members
		hknpDynamicCompoundShapeData* boundingVolumeData; // C0
	};
	static_assert(sizeof(hknpDynamicCompoundShape) == 0xD0);
}
