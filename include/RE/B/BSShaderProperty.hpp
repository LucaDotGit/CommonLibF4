#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/N/NiShadeProperty.hpp"

namespace RE
{
	class BSEffectShaderData;
	class BSRenderPass;
	class BSShaderAccumulator;
	class BSShaderMaterial;
	class NiTexture;

	class __declspec(novtable) BSShaderProperty
		: public NiShadeProperty // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSShaderProperty };
		inline static constexpr auto VTABLE{ VTABLE::BSShaderProperty };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::BSShaderProperty };

		enum class TextureTypeEnum : std::int32_t
		{
			kBase = 0,
			kNormal = 1,
			kGlow = 2,
			kHeight = 3,
			kEnv = 4,
			kWrinkles = 5,
			kMultilayer = 6,
			kBacklightMask = 7,
			kSmoothSpec = kBacklightMask,

			kTotal = 8
		};

		enum class EShaderPropertyFlags : std::uint64_t
		{
			kNone = 0,
			kSpecular = 1ui64 << 0,
			kSkinned = 1ui64 << 1,
			kTempRefraction = 1ui64 << 2,
			kVertexAlpha = 1ui64 << 3,
			kGrayscaleToPaletteColor = 1ui64 << 4,
			kGrayscaleToPaletteAlpha = 1ui64 << 5,
			kFalloff = 1ui64 << 6,
			kEnvMap = 1ui64 << 7,
			kRGBFalloff = 1ui64 << 8,
			kCastShadows = 1ui64 << 9,
			kFace = 1ui64 << 10,
			kUIMaskRects = 1ui64 << 11,
			kModelSpaceNormals = 1ui64 << 12,
			kRefractionClamp = 1ui64 << 13,
			kMultiTextureLandscape = 1ui64 << 14,
			kRefraction = 1ui64 << 15,
			kRefractionFalloff = 1ui64 << 16,
			kEyeReflect = 1ui64 << 17,
			kHairTint = 1ui64 << 18,
			kScreendoorAlphaFade = 1ui64 << 19,
			kLocalMapClear = 1ui64 << 20,
			kFaceGenRGBTint = 1ui64 << 21,
			kOwnEmit = 1ui64 << 22,
			kProjectedUV = 1ui64 << 23,
			kMultipleTextures = 1ui64 << 24,
			kTesselate = 1ui64 << 25,
			kDecal = 1ui64 << 26,
			kDynamicDecal = 1ui64 << 27,
			kCharacterLight = 1ui64 << 28,
			kExternalEmittance = 1ui64 << 29,
			kSoftEffect = 1ui64 << 30,
			kZBufferTest = 1ui64 << 31,
			kZBufferWrite = 1ui64 << 32,
			kLODLandscape = 1ui64 << 33,
			kLODObjects = 1ui64 << 34,
			kNoFade = 1ui64 << 35,
			kTwoSided = 1ui64 << 36,
			kVertexColors = 1ui64 << 37,
			kGlowMap = 1ui64 << 38,
			kTransformChanged = 1ui64 << 39,
			kDismembermentMeatCuff = 1ui64 << 40,
			kTint = 1ui64 << 41,
			kVertexLighting = 1ui64 << 42,
			kUniformScale = 1ui64 << 43,
			kFitSlope = 1ui64 << 44,
			kBillboard = 1ui64 << 45,
			kLODLandBlend = 1ui64 << 46,
			kDismemberment = 1ui64 << 47,
			kWireframe = 1ui64 << 48,
			kWeaponBlood = 1ui64 << 49,
			kHideOnLocalMap = 1ui64 << 50,
			kPremultAlpha = 1ui64 << 51,
			kVATSTarget = 1ui64 << 52,
			kAnisotropicLighting = 1ui64 << 53,
			kSkewSpecularAlpha = 1ui64 << 54,
			kMenuScreen = 1ui64 << 55,
			kMultiLayerParallax = 1ui64 << 56,
			kAlphaTest = 1ui64 << 57,
			kInvertedFadePattern = 1ui64 << 58,
			kVATSTargetDrawAll = 1ui64 << 59,
			kPipboyScreen = 1ui64 << 60,
			kTreeAnim = 1ui64 << 61,
			kEffectLighting = 1ui64 << 62,
			kRefractionWritesDepth = 1ui64 << 63
		};

		class ForEachVisitor;

		class RenderPassArray
		{
		public:
			// members
			BSRenderPass* passList{ nullptr }; // 00
		};
		static_assert(sizeof(RenderPassArray) == 0x08);

		// add
		virtual RenderPassArray* GetRenderPasses(BSGeometry* a_geom, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator) = 0;			  // 2B
		virtual RenderPassArray* GetRenderPasses_ShadowMapOrMask(BSGeometry* a_geom, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator); // 2C - { return nullptr; }
		virtual RenderPassArray* GetRenderPasses_LocalMap(BSGeometry* a_geom, std::uint32_t a_renderMode, BSShaderAccumulator* a_accumulator);		  // 2D - { return nullptr; }
		virtual BSRenderPass* CreateVatsMaskRenderPass(BSGeometry* a_geom);																			  // 2E - { return nullptr; }
		virtual std::uint16_t GetNumberofPasses(BSGeometry* a_geom);																				  // 2F - { return 1; }
		virtual BSRenderPass* GetRenderDepthPass(BSGeometry* a_geom);																				  // 30 - { return nullptr; }
		virtual bool CanMerge(const BSShaderProperty* a_prop);																						  // 31
		virtual void SetMaterialAlpha(REX::Float32 a_alpha);																						  // 32 - { return; }
		virtual REX::Float32 QMaterialAlpha() const;																								  // 33 - { return 1.0_f32; }
		virtual const BSFixedString& GetRootName() const;																							  // 34
		virtual std::int32_t ForEachTexture(ForEachVisitor& a_visitor);																				  // 35 - { return 1; }
		virtual std::int32_t QShader() const;																										  // 36 - { return 0; }
		virtual void ClearUnusedMaterialValues();																									  // 37 - { return; }
		virtual BSShaderProperty* ClarifyShader(BSGeometry* a_geom, bool a_unk01, bool a_unk02);													  // 38 - { return nullptr; }
		virtual NiTexture* GetBaseTexture() const;																									  // 39 - { return nullptr; }
		virtual RenderPassArray* GetWaterFogPassList(BSGeometry* a_geom);																			  // 3A - { return nullptr; }
		virtual bool AcceptsEffectData() const;																										  // 3B - { return false; }
		virtual void PrecacheTextures();																											  // 3C - { return; }
		virtual std::uint32_t DetermineUtilityShaderDecl() const;																					  // 3D - { return 0; }
		virtual std::uint32_t GetMaterialType() const;																								  // 3E - { return 0; }
		virtual void DoClearRenderPasses();																											  // 3F - { return; }

		void SetMaterial(BSShaderMaterial* a_material, bool a_unique)
		{
			using FuncType = decltype(&BSShaderProperty::SetMaterial);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSShaderProperty::SetMaterial };
			FUNC(this, a_material, a_unique);
		}

		// members
		REX::Float32 alpha;										 // 28
		std::int32_t lastRenderPassState;						 // 2C
		REX::EnumSet<EShaderPropertyFlags, std::uint64_t> flags; // 30
		RenderPassArray renderPassList;							 // 38
		RenderPassArray debugRenderPassList;					 // 40
		BSFadeNode* fadeNode;									 // 48
		BSEffectShaderData* effectData;							 // 50
		BSShaderMaterial* material;								 // 58
		std::uint32_t lastAccumTime;							 // 60
		REX::Float32 lodFade;									 // 64
		mutable BSNonReentrantSpinLock clearRenderPassesLock;	 // 68
	};
	static_assert(sizeof(BSShaderProperty) == 0x70);
}
