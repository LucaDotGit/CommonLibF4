#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiAlphaProperty.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::BSGraphics
{
	enum class TextureAddressMode : std::int32_t;
}

namespace RE
{
	class BSEffectShaderPropertyColorController;
	class BSEffectShaderPropertyFloatController;
	class BSLightingShaderPropertyColorController;
	class BSLightingShaderPropertyFloatController;
	class BSLightingShaderPropertyUShortController;
	class BSNiAlphaPropertyTestRefController;
	class BSShaderTextureSet;

	class BSShaderData
		: public BSIntrusiveRefCounted // 00
	{
	public:
		enum class LightingShaderEnum : std::int32_t
		{
			kStandard = 0,
			kWater = 1,
			kEffect = 2,
			kSky = 3,
			kTallGrass = 4
		};

		// members
		REX::Enum<LightingShaderEnum, std::int32_t> lightingShader;					   // 004
		bool specularEnabled;														   // 008
		NiColor specularColor;														   // 00C
		REX::Float32 specularMult;													   // 018
		NiColor emittanceColor;														   // 01C
		REX::Float32 emittanceColorScale;											   // 028
		REX::Float32 lightingInfluence;												   // 02C
		std::int8_t envmapMinLOD;													   // 030
		REX::Float32 smoothness;													   // 034
		REX::Float32 fresnelPower_ShaderDataEntry;									   // 038
		REX::Float32 wetnessControl_SpecScale_ShaderDataEntry;						   // 03C
		REX::Float32 wetnessControl_SpecPowerScale_ShaderDataEntry;					   // 040
		REX::Float32 wetnessControl_SpecMin_ShaderDataEntry;						   // 044
		REX::Float32 wetnessControl_EnvMapScale_ShaderDataEntry;					   // 048
		REX::Float32 wetnessControl_FresnelPower_ShaderDataEntry;					   // 04C
		REX::Float32 wetnessControl_Metalness_ShaderDataEntry;						   // 050
		bool betnessControl_ScreenSpaceReflections;									   // 054
		BSFixedString rootMaterialPath;												   // 058
		REX::Float32 alpha;															   // 060
		REX::Float32 emittanceMult;													   // 064
		REX::Float32 lookupScale;													   // 068
		bool emitEnabled;															   // 06C
		BSFixedString materialPath;													   // 070
		bool alphaBlend;															   // 078
		REX::Enum<NiAlphaProperty::AlphaFunction, std::int32_t> alphaSrcBlendMode;	   // 07C
		REX::Enum<NiAlphaProperty::AlphaFunction, std::int32_t> alphaDestBlendMode;	   // 080
		bool alphaTest;																   // 084
		REX::Enum<NiAlphaProperty::TestFunction, std::int32_t> alphaTestFunction;	   // 088
		std::int8_t alphaTestRef;													   // 08C
		bool enableEditorAlphaRef;													   // 08D
		bool vertexColors;															   // 08E
		bool vertexAlpha;															   // 08F
		bool modelSpaceNormals;														   // 090
		bool decal;																	   // 091
		bool externalEmittance;														   // 092
		bool hideSecret;															   // 093
		bool noFade;																   // 094
		bool dismemberment;															   // 095
		bool facegen;																   // 096
		bool skinTint;																   // 097
		bool hair;																	   // 098
		bool twoSided;																   // 099
		bool tree;																	   // 09A
		bool bloodEnabled;															   // 09B
		bool uniqueAlphaProperty;													   // 09C
		bool effectLightingEnabled;													   // 09D
		bool castShadows;															   // 09E
		bool receiveShadows;														   // 09F
		bool dissolveFade;															   // 0A0
		bool glowmap;																   // 0A1
		bool assumeShadowmask;														   // 0A2
		bool screenSpaceReflections;												   // 0A3
		bool nonOccluder;															   // 0A4
		bool skewSpecularAlpha;														   // 0A5
		bool tessellate;															   // 0A6
		bool backLighting;															   // 0A7
		bool subSurfaceLighting;													   // 0A8
		bool rimLighting;															   // 0A9
		REX::Float32 subSurfaceRolloff;												   // 0AC
		REX::Float32 rimPower;														   // 0B0
		REX::Float32 backLightPower;												   // 0B4
		bool anisoLighting;															   // 0B8
		bool zBufferWrite;															   // 0B8
		bool zBufferTest;															   // 0BA
		bool refraction;															   // 0BB
		REX::Float32 refractionPower;												   // 0BC
		bool refractionFalloff;														   // 0C0
		BSTArray<BSLightingShaderPropertyFloatController*> lightingFloatControllers;   // 0C8
		BSTArray<BSLightingShaderPropertyUShortController*> lightingUShortControllers; // 0E0
		BSTArray<BSLightingShaderPropertyColorController*> lightingColorControllers;   // 0F8
		BSTArray<BSEffectShaderPropertyFloatController*> effectFloatControllers;	   // 110
		BSTArray<BSEffectShaderPropertyColorController*> effectColorControllers;	   // 128
		BSNiAlphaPropertyTestRefController* alphaRefTestController;					   // 140
		bool parallax;																   // 148
		bool parallaxOcclusion;														   // 149
		bool multiLayerParallax;													   // 14A
		REX::Float32 parallaxOcclusionHeightScale;									   // 14C
		REX::Float32 parallaxOcclusionMaxPasses;									   // 150
		REX::Float32 parallaxLayerThickness;										   // 154
		REX::Float32 parallaxRefractionScale;										   // 158
		REX::Float32 parallaxInnerLayerUScale;										   // 15C
		REX::Float32 parallaxInnerLayerVScale;										   // 160
		REX::Float32 displacementTextureBias;										   // 164
		REX::Float32 displacementTextureScale;										   // 168
		REX::Float32 tessellationPNScale;											   // 16C
		REX::Float32 tessellationFadeDistance;										   // 170
		REX::Float32 tessellationBaseFactor;										   // 174
		bool tessellationNeedsDominantUVs;											   // 178
		bool tessellationNeedsCrackFreeNormals;										   // 179
		bool environmentMapping;													   // 17A
		bool environmentMappingEye;													   // 17B
		bool environmentMappingWindow;												   // 17C
		REX::Float32 environmentMappingMaskScale;									   // 180
		std::int32_t skyTYpe;														   // 184
		bool reflectionsEnabled;													   // 188
		bool silhouetteReflectionsEnabled;											   // 189
		bool refractionsEnabled;													   // 18A
		bool depthEnabled;															   // 18B
		bool vertexUVEnabled;														   // 18C
		bool vertexAlphaDepthEnabled;												   // 18D
		bool foggingEnabled;														   // 18E
		bool falloffEnabled;														   // 18F
		bool rgbFalloffEnabled;														   // 190
		NiColorA falloffData;														   // 194
		bool softEnabled;															   // 1A4
		REX::Float32 softDepth;														   // 1A8
		NiPoint2 uvOffset;															   // 1AC
		NiPoint2 uvScale;															   // 1B4
		bool grayscaleToPaletteColor;												   // 1BC
		bool grayscaleToPaletteAlpha;												   // 1BD
		NiColor hairTintColor;														   // 1C0
		NiPointer<BSShaderTextureSet> textureSet;									   // 1D0
		REX::Enum<BSGraphics::TextureAddressMode, std::int32_t> clampMode;			   // 1D8
	};
	static_assert(sizeof(BSShaderData) == 0x1E0);
}
