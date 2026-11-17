#pragma once

#include "RE/B/BSShaderMaterial.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPlane.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSWaterShaderMaterial : public BSShaderMaterial // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSWaterShaderMaterial;
		inline static constexpr const auto& VTABLE = VTABLE::BSWaterShaderMaterial;

		~BSWaterShaderMaterial() override; // 0x00

		// members
		NiPointer<NiTexture> staticReflectionMap; // 0x038
		NiPointer<NiTexture> normalMap01;		  // 0x040
		NiPointer<NiTexture> normalMap02;		  // 0x048
		NiPointer<NiTexture> normalMap03;		  // 0x050
		NiColorA shallowColor;					  // 0x058
		NiColorA deepColor;						  // 0x068
		NiColorA reflectionColor;				  // 0x078
		NiColorA underwaterFogColor;			  // 0x088
		NiColorA lightSiltColor;				  // 0x090
		NiColorA darkSiltcolor;					  // 0x0A8
		NiColorA varAmounts;					  // 0x0B8
		NiColorA waterParams01;					  // 0x0C8
		NiColorA waterParams02;					  // 0x0D8
		NiColorA waterParams03;					  // 0x0E8
		NiColorA waterParams04;					  // 0x0F8
		NiColorA normalsScroll01;				  // 0x108
		NiColorA normalsScroll02;				  // 0x118
		NiColorA normalsScale;					  // 0x128
		NiColorA normalsAmplitude;				  // 0x138
		NiPlane reflectionPlane;				  // 0x148
		std::int32_t texOffsetX;				  // 0x158
		std::int32_t texOffsetY;				  // 0x15C
		bool updateConstants;					  // 0x160
		bool useDefaultReflectionTexture;		  // 0x161
		bool useSSR;							  // 0x162
	};

	static_assert(sizeof(BSWaterShaderMaterial) == 0x168);
}
