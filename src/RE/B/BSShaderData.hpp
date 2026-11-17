#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiAlphaProperty.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPoint2.hpp"
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

	class BSShaderData : public BSIntrusiveRefCounted // 0x00
	{
	public:
		enum class LightingShaderEnum : std::int32_t
		{
			Standard = 0,
			Water = 1,
			Effect = 2,
			Sky = 3,
			TallGrass = 4
		};

		// members
		REX::Enum<LightingShaderEnum, std::int32_t> lightingShader;					   // 0x004
		bool specularEnabled;														   // 0x008
		NiColor specularColor;														   // 0x00C
		REX::Float32 specularMult;													   // 0x018
		NiColor emittanceColor;														   // 0x01C
		REX::Float32 emittanceColorScale;											   // 0x028
		REX::Float32 lightingInfluence;												   // 0x02C
		std::int8_t envmapMinLOD;													   // 0x030
		REX::Float32 smoothness;													   // 0x034
		REX::Float32 fresnelPowerShaderDataEntry;									   // 0x038
		REX::Float32 wetnessControlSpecScaleShaderDataEntry;						   // 0x03C
		REX::Float32 wetnessControlSpecPowerScaleShaderDataEntry;					   // 0x040
		REX::Float32 wetnessControlSpecMinShaderDataEntry;							   // 0x044
		REX::Float32 wetnessControlEnvMapScaleShaderDataEntry;						   // 0x048
		REX::Float32 wetnessControlFresnelPowerShaderDataEntry;						   // 0x04C
		REX::Float32 wetnessControlMetalnessShaderDataEntry;						   // 0x050
		bool wetnessControlScreenSpaceReflections;									   // 0x054
		BSFixedString rootMaterialPath;												   // 0x058
		REX::Float32 alpha;															   // 0x060
		REX::Float32 emittanceMult;													   // 0x064
		REX::Float32 lookupScale;													   // 0x068
		bool emitEnabled;															   // 0x06C
		BSFixedString materialPath;													   // 0x070
		bool alphaBlend;															   // 0x078
		REX::Enum<NiAlphaProperty::AlphaFunction, std::int32_t> alphaSrcBlendMode;	   // 0x07C
		REX::Enum<NiAlphaProperty::AlphaFunction, std::int32_t> alphaDestBlendMode;	   // 0x080
		bool alphaTest;																   // 0x084
		REX::Enum<NiAlphaProperty::TestFunction, std::int32_t> alphaTestFunction;	   // 0x088
		std::int8_t alphaTestRef;													   // 0x08C
		bool enableEditorAlphaRef;													   // 0x08D
		bool vertexColors;															   // 0x08E
		bool vertexAlpha;															   // 0x08F
		bool modelSpaceNormals;														   // 0x090
		bool decal;																	   // 0x091
		bool externalEmittance;														   // 0x092
		bool hideSecret;															   // 0x093
		bool noFade;																   // 0x094
		bool dismemberment;															   // 0x095
		bool facegen;																   // 0x096
		bool skinTint;																   // 0x097
		bool hair;																	   // 0x098
		bool twoSided;																   // 0x099
		bool tree;																	   // 0x09A
		bool bloodEnabled;															   // 0x09B
		bool uniqueAlphaProperty;													   // 0x09C
		bool effectLightingEnabled;													   // 0x09D
		bool castShadows;															   // 0x09E
		bool receiveShadows;														   // 0x09F
		bool dissolveFade;															   // 0x0A0
		bool glowmap;																   // 0x0A1
		bool assumeShadowmask;														   // 0x0A2
		bool screenSpaceReflections;												   // 0x0A3
		bool nonOccluder;															   // 0x0A4
		bool skewSpecularAlpha;														   // 0x0A5
		bool tessellate;															   // 0x0A6
		bool backLighting;															   // 0x0A7
		bool subSurfaceLighting;													   // 0x0A8
		bool rimLighting;															   // 0x0A9
		REX::Float32 subSurfaceRolloff;												   // 0x0AC
		REX::Float32 rimPower;														   // 0x0B0
		REX::Float32 backLightPower;												   // 0x0B4
		bool anisoLighting;															   // 0x0B8
		bool zBufferWrite;															   // 0x0B8
		bool zBufferTest;															   // 0x0BA
		bool refraction;															   // 0x0BB
		REX::Float32 refractionPower;												   // 0x0BC
		bool refractionFalloff;														   // 0x0C0
		BSTArray<BSLightingShaderPropertyFloatController*> lightingFloatControllers;   // 0x0C8
		BSTArray<BSLightingShaderPropertyUShortController*> lightingUShortControllers; // 0x0E0
		BSTArray<BSLightingShaderPropertyColorController*> lightingColorControllers;   // 0x0F8
		BSTArray<BSEffectShaderPropertyFloatController*> effectFloatControllers;	   // 0x110
		BSTArray<BSEffectShaderPropertyColorController*> effectColorControllers;	   // 0x128
		BSNiAlphaPropertyTestRefController* alphaRefTestController;					   // 0x140
		bool parallax;																   // 0x148
		bool parallaxOcclusion;														   // 0x149
		bool multiLayerParallax;													   // 0x14A
		REX::Float32 parallaxOcclusionHeightScale;									   // 0x14C
		REX::Float32 parallaxOcclusionMaxPasses;									   // 0x150
		REX::Float32 parallaxLayerThickness;										   // 0x154
		REX::Float32 parallaxRefractionScale;										   // 0x158
		REX::Float32 parallaxInnerLayerUScale;										   // 0x15C
		REX::Float32 parallaxInnerLayerVScale;										   // 0x160
		REX::Float32 displacementTextureBias;										   // 0x164
		REX::Float32 displacementTextureScale;										   // 0x168
		REX::Float32 tessellationPNScale;											   // 0x16C
		REX::Float32 tessellationFadeDistance;										   // 0x170
		REX::Float32 tessellationBaseFactor;										   // 0x174
		bool tessellationNeedsDominantUVs;											   // 0x178
		bool tessellationNeedsCrackFreeNormals;										   // 0x179
		bool environmentMapping;													   // 0x17A
		bool environmentMappingEye;													   // 0x17B
		bool environmentMappingWindow;												   // 0x17C
		REX::Float32 environmentMappingMaskScale;									   // 0x180
		std::int32_t skyTYpe;														   // 0x184
		bool reflectionsEnabled;													   // 0x188
		bool silhouetteReflectionsEnabled;											   // 0x189
		bool refractionsEnabled;													   // 0x18A
		bool depthEnabled;															   // 0x18B
		bool vertexUVEnabled;														   // 0x18C
		bool vertexAlphaDepthEnabled;												   // 0x18D
		bool foggingEnabled;														   // 0x18E
		bool falloffEnabled;														   // 0x18F
		bool rgbFalloffEnabled;														   // 0x190
		NiColorA falloffData;														   // 0x194
		bool softEnabled;															   // 0x1A4
		REX::Float32 softDepth;														   // 0x1A8
		NiPoint2 uvOffset;															   // 0x1AC
		NiPoint2 uvScale;															   // 0x1B4
		bool grayscaleToPaletteColor;												   // 0x1BC
		bool grayscaleToPaletteAlpha;												   // 0x1BD
		NiColor hairTintColor;														   // 0x1C0
		NiPointer<BSShaderTextureSet> textureSet;									   // 0x1D0
		REX::Enum<BSGraphics::TextureAddressMode, std::int32_t> clampMode;			   // 0x1D8
	};

	static_assert(sizeof(BSShaderData) == 0x1E0);
}
