#pragma once

#include "RE/B/BSLightingShaderMaterialBase.hpp"

namespace RE
{
	class __declspec(novtable) BSLightingShaderMaterial
		: public BSLightingShaderMaterialBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLightingShaderMaterial };
		inline static constexpr auto VTABLE{ VTABLE::BSLightingShaderMaterial };
	};
	static_assert(sizeof(BSLightingShaderMaterial) == 0xC0);
}
