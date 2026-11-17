#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSNonReentrantSpinLock.hpp"
#include "RE/N/NiShadeProperty.hpp"

namespace RE
{
	class BSEffectShaderData;
	class BSRenderPass;
	class BSShaderAccumulator;
	class BSShaderMaterial;
	class NiTexture;

	class __declspec(novtable) BSShaderProperty : public NiShadeProperty // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSShaderProperty;
		inline static constexpr const auto& VTABLE = VTABLE::BSShaderProperty;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::BSShaderProperty;

		enum class TextureType : std::int32_t
		{
			Diffuse = 0,
			Normal = 1,
			Glow = 2,
			Height = 3,
			Environment = 4,
			Wrinkles = 5,
			Multilayer = 6,
			BacklightMask = 7,
			SmoothSpec = BacklightMask,

			_Count = 8
		};

		enum class ShaderPropertyFlags : std::uint64_t
		{
			None = 0,
			Specular = static_cast<std::uint64_t>(1) << 0,
			Skinned = static_cast<std::uint64_t>(1) << 1,
			TempRefraction = static_cast<std::uint64_t>(1) << 2,
			VertexAlpha = static_cast<std::uint64_t>(1) << 3,
			GrayscaleToPaletteColor = static_cast<std::uint64_t>(1) << 4,
			GrayscaleToPaletteAlpha = static_cast<std::uint64_t>(1) << 5,
			Falloff = static_cast<std::uint64_t>(1) << 6,
			EnvMap = static_cast<std::uint64_t>(1) << 7,
			RGBFalloff = static_cast<std::uint64_t>(1) << 8,
			CastShadows = static_cast<std::uint64_t>(1) << 9,
			Face = static_cast<std::uint64_t>(1) << 10,
			UIMaskRects = static_cast<std::uint64_t>(1) << 11,
			ModelSpaceNormals = static_cast<std::uint64_t>(1) << 12,
			RefractionClamp = static_cast<std::uint64_t>(1) << 13,
			MultiTextureLandscape = static_cast<std::uint64_t>(1) << 14,
			Refraction = static_cast<std::uint64_t>(1) << 15,
			RefractionFalloff = static_cast<std::uint64_t>(1) << 16,
			EyeReflect = static_cast<std::uint64_t>(1) << 17,
			HairTint = static_cast<std::uint64_t>(1) << 18,
			ScreendoorAlphaFade = static_cast<std::uint64_t>(1) << 19,
			LocalMapClear = static_cast<std::uint64_t>(1) << 20,
			FaceGenRGBTint = static_cast<std::uint64_t>(1) << 21,
			OwnEmit = static_cast<std::uint64_t>(1) << 22,
			ProjectedUV = static_cast<std::uint64_t>(1) << 23,
			MultipleTextures = static_cast<std::uint64_t>(1) << 24,
			Tesselate = static_cast<std::uint64_t>(1) << 25,
			Decal = static_cast<std::uint64_t>(1) << 26,
			DynamicDecal = static_cast<std::uint64_t>(1) << 27,
			CharacterLight = static_cast<std::uint64_t>(1) << 28,
			ExternalEmittance = static_cast<std::uint64_t>(1) << 29,
			SoftEffect = static_cast<std::uint64_t>(1) << 30,
			ZBufferTest = static_cast<std::uint64_t>(1) << 31,
			ZBufferWrite = static_cast<std::uint64_t>(1) << 32,
			LODLandscape = static_cast<std::uint64_t>(1) << 33,
			LODObjects = static_cast<std::uint64_t>(1) << 34,
			NoFade = static_cast<std::uint64_t>(1) << 35,
			TwoSided = static_cast<std::uint64_t>(1) << 36,
			VertexColors = static_cast<std::uint64_t>(1) << 37,
			GlowMap = static_cast<std::uint64_t>(1) << 38,
			TransformChanged = static_cast<std::uint64_t>(1) << 39,
			DismembermentMeatCuff = static_cast<std::uint64_t>(1) << 40,
			Tint = static_cast<std::uint64_t>(1) << 41,
			VertexLighting = static_cast<std::uint64_t>(1) << 42,
			UniformScale = static_cast<std::uint64_t>(1) << 43,
			FitSlope = static_cast<std::uint64_t>(1) << 44,
			Billboard = static_cast<std::uint64_t>(1) << 45,
			LODLandBlend = static_cast<std::uint64_t>(1) << 46,
			Dismemberment = static_cast<std::uint64_t>(1) << 47,
			Wireframe = static_cast<std::uint64_t>(1) << 48,
			WeaponBlood = static_cast<std::uint64_t>(1) << 49,
			HideOnLocalMap = static_cast<std::uint64_t>(1) << 50,
			PremultAlpha = static_cast<std::uint64_t>(1) << 51,
			VATSTarget = static_cast<std::uint64_t>(1) << 52,
			AnisotropicLighting = static_cast<std::uint64_t>(1) << 53,
			SkewSpecularAlpha = static_cast<std::uint64_t>(1) << 54,
			MenuScreen = static_cast<std::uint64_t>(1) << 55,
			MultiLayerParallax = static_cast<std::uint64_t>(1) << 56,
			AlphaTest = static_cast<std::uint64_t>(1) << 57,
			InvertedFadePattern = static_cast<std::uint64_t>(1) << 58,
			VATSTargetDrawAll = static_cast<std::uint64_t>(1) << 59,
			PipboyScreen = static_cast<std::uint64_t>(1) << 60,
			TreeAnim = static_cast<std::uint64_t>(1) << 61,
			EffectLighting = static_cast<std::uint64_t>(1) << 62,
			RefractionWritesDepth = static_cast<std::uint64_t>(1) << 63
		};

		class ForEachVisitor;

		class RenderPassArray
		{
		public:
			// members
			BSRenderPass* passList{nullptr}; // 0x00
		};

		static_assert(sizeof(RenderPassArray) == 0x08);

		~BSShaderProperty() override; // 0x00

		// add
		virtual auto GetRenderPasses(
			BSGeometry* a_geom,
			std::uint32_t a_renderMode,
			BSShaderAccumulator* a_accumulator) -> RenderPassArray* = 0; // 0x2B
		virtual auto GetRenderPasses_ShadowMapOrMask(
			BSGeometry* a_geom,
			std::uint32_t a_renderMode,
			BSShaderAccumulator* a_accumulator) -> RenderPassArray*; // 0x2C - { return nullptr; }
		virtual auto GetRenderPasses_LocalMap(
			BSGeometry* a_geom,
			std::uint32_t a_renderMode,
			BSShaderAccumulator* a_accumulator) -> RenderPassArray*;				// 0x2D - { return nullptr; }
		virtual auto CreateVatsMaskRenderPass(BSGeometry* a_geom) -> BSRenderPass*; // 0x2E - { return nullptr; }
		virtual auto GetNumberofPasses(BSGeometry* a_geom) -> std::uint16_t;		// 0x2F - { return 1; }
		virtual auto GetRenderDepthPass(BSGeometry* a_geom) -> BSRenderPass*;		// 0x30 - { return nullptr; }
		virtual auto CanMerge(const BSShaderProperty* a_prop) -> bool;				// 0x31
		virtual void SetMaterialAlpha(REX::Float32 a_alpha);						// 0x32 - { return; }
		virtual auto QMaterialAlpha() const -> REX::Float32;	  // 0x33 - { return static_cast<REX::Float32>(1.0); }
		virtual auto GetRootName() const -> const BSFixedString&; // 0x34
		virtual auto ForEachTexture(ForEachVisitor& a_visitor) -> std::int32_t; // 0x35 - { return 1; }
		virtual auto QShader() const -> std::int32_t;							// 0x36 - { return 0; }
		virtual void ClearUnusedMaterialValues();								// 0x37 - { return; }
		virtual auto ClarifyShader(
			BSGeometry* a_geom,
			bool a_unk01,
			bool a_unk02) -> BSShaderProperty*;									  // 0x38 - { return nullptr; }
		virtual auto GetBaseTexture() const -> NiTexture*;						  // 0x39 - { return nullptr; }
		virtual auto GetWaterFogPassList(BSGeometry* a_geom) -> RenderPassArray*; // 0x3A - { return nullptr; }
		virtual auto AcceptsEffectData() const -> bool;							  // 0x3B - { return false; }
		virtual void PrecacheTextures();										  // 0x3C - { return; }
		virtual auto DetermineUtilityShaderDecl() const -> std::uint32_t;		  // 0x3D - { return 0; }
		virtual auto GetMaterialType() const -> std::uint32_t;					  // 0x3E - { return 0; }
		virtual void DoClearRenderPasses();										  // 0x3F - { return; }

		void SetMaterial(BSShaderMaterial* a_material, bool a_unique)
		{
			using FuncType = decltype(&BSShaderProperty::SetMaterial);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSShaderProperty::SetMaterial);
			std::invoke(FUNC, this, a_material, a_unique);
		}

		// members
		REX::Float32 alpha;										// 0x28
		std::int32_t lastRenderPassState;						// 0x2C
		REX::EnumSet<ShaderPropertyFlags, std::uint64_t> flags; // 0x30
		RenderPassArray renderPassList;							// 0x38
		RenderPassArray debugRenderPassList;					// 0x40
		BSFadeNode* fadeNode;									// 0x48
		BSEffectShaderData* effectData;							// 0x50
		BSShaderMaterial* material;								// 0x58
		std::uint32_t lastAccumTime;							// 0x60
		REX::Float32 lodFade;									// 0x64
		mutable BSNonReentrantSpinLock clearRenderPassesLock;	// 0x68
	};

	static_assert(sizeof(BSShaderProperty) == 0x70);
}
