#pragma once

#include "RE/B/BSShaderMaterial.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPlane.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiTexture;

	class __declspec(novtable) BSWaterShaderMaterial
		: public BSShaderMaterial // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSWaterShaderMaterial };
		inline static constexpr auto VTABLE{ VTABLE::BSWaterShaderMaterial };

		~BSWaterShaderMaterial() override; // 00

		// members
		NiPointer<NiTexture> staticReflectionMap; // 038
		NiPointer<NiTexture> normalMap01;		  // 040
		NiPointer<NiTexture> normalMap02;		  // 048
		NiPointer<NiTexture> normalMap03;		  // 050
		NiColorA shallowColor;					  // 058
		NiColorA deepColor;						  // 068
		NiColorA reflectionColor;				  // 078
		NiColorA underwaterFogColor;			  // 088
		NiColorA lightSiltColor;				  // 090
		NiColorA darkSiltcolor;					  // 0A8
		NiColorA varAmounts;					  // 0B8
		NiColorA waterParams01;					  // 0C8
		NiColorA waterParams02;					  // 0D8
		NiColorA waterParams03;					  // 0E8
		NiColorA waterParams04;					  // 0F8
		NiColorA normalsScroll01;				  // 108
		NiColorA normalsScroll02;				  // 118
		NiColorA normalsScale;					  // 128
		NiColorA normalsAmplitude;				  // 138
		NiPlane reflectionPlane;				  // 148
		std::int32_t texOffsetX;				  // 158
		std::int32_t texOffsetY;				  // 15C
		bool updateConstants;					  // 160
		bool useDefaultReflectionTexture;		  // 161
		bool useSSR;							  // 162
	};
	static_assert(sizeof(BSWaterShaderMaterial) == 0x168);
}
