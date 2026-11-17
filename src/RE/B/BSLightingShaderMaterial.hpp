#pragma once

#include "RE/B/BSLightingShaderMaterialBase.hpp"

namespace RE
{
	class __declspec(novtable) BSLightingShaderMaterial : public BSLightingShaderMaterialBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSLightingShaderMaterial;
		inline static constexpr const auto& VTABLE = VTABLE::BSLightingShaderMaterial;
	};

	static_assert(sizeof(BSLightingShaderMaterial) == 0xC0);
}
