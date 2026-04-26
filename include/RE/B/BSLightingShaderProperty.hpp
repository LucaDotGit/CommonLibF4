#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSShaderProperty.hpp"
#include "RE/N/NiColor.hpp"

namespace RE
{
	class __declspec(novtable) BSLightingShaderProperty
		: public BSShaderProperty // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSLightingShaderProperty };
		inline static constexpr auto VTABLE{ VTABLE::BSLightingShaderProperty };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSLightingShaderProperty };

		// members
		NiColorA projectedUVParams;							   // 70
		NiColorA projectedUVColor;							   // 80
		std::array<RenderPassArray, 3> depthMapRenderPassList; // 90
		BSRenderPass* depthRenderPass;						   // A8
		RenderPassArray forwardPassList;					   // B0
		NiColor* emitColor;									   // B8
		BSFixedString rootName;								   // C0
		REX::Float32 emitColorScale;						   // C8
		REX::Float32 forcedDarkness;						   // CC
		REX::Float32 specularLODFade;						   // D0
		REX::Float32 envmapLODFade;							   // D4
		std::uint32_t baseTechniqueID;						   // D8
		std::uint32_t clearCommandBufferCount;				   // DC
		std::uint16_t debugTintIndex;						   // E0
		std::uint32_t stencilRef;							   // E4
	};
	static_assert(sizeof(BSLightingShaderProperty) == 0xE8);
}
