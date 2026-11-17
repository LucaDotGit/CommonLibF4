#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSShaderProperty.hpp"
#include "RE/N/NiColorA.hpp"

namespace RE
{
	class NiColor;

	class __declspec(novtable) BSLightingShaderProperty : public BSShaderProperty // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSLightingShaderProperty;
		inline static constexpr const auto& VTABLE = VTABLE::BSLightingShaderProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSLightingShaderProperty;

		~BSLightingShaderProperty() override; // 0x00

		// members
		NiColorA projectedUVParams;							   // 0x70
		NiColorA projectedUVColor;							   // 0x80
		std::array<RenderPassArray, 3> depthMapRenderPassList; // 0x90
		BSRenderPass* depthRenderPass;						   // 0xA8
		RenderPassArray forwardPassList;					   // 0xB0
		NiColor* emitColor;									   // 0xB8
		BSFixedString rootName;								   // 0xC0
		REX::Float32 emitColorScale;						   // 0xC8
		REX::Float32 forcedDarkness;						   // 0xCC
		REX::Float32 specularLODFade;						   // 0xD0
		REX::Float32 envmapLODFade;							   // 0xD4
		std::uint32_t baseTechniqueID;						   // 0xD8
		std::uint32_t clearCommandBufferCount;				   // 0xDC
		std::uint16_t debugTintIndex;						   // 0xE0
		std::uint32_t stencilRef;							   // 0xE4
	};

	static_assert(sizeof(BSLightingShaderProperty) == 0xE8);
}
