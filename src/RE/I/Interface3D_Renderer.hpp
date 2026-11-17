#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/I/Interface3D_OldScrreenEffectControl.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/U/UIShaderFXInfo.hpp"

namespace RE
{
	enum class UI_DEPTH_PRIORITY : std::int32_t;

	class BSGeometry;
	class BSShaderAccumulator;
	class NiAVObject;
	class NiCamera;
	class NiDirectionalLight;
	class NiLight;
	class ShadowSceneNode;
}

namespace Scaleform::GFx
{
	class Movie;
}

namespace RE::Interface3D
{
	enum class BackgroundMode : std::int32_t;
	enum class HighlightEffect : std::int32_t;
	enum class LightType : std::int32_t;
	enum class OffscreenMenuBlendMode : std::int32_t;
	enum class OffscreenMenuSize : std::int32_t;
	enum class PostEffect : std::int32_t;
	enum class ScreenMode : std::int32_t;

	class Renderer
	{
	public:
		class LightParams
		{
		public:
			// members
			REX::Enum<LightType, std::int32_t> type; // 0x00
			REX::Float32 spotFOV;					 // 0x04
			NiPoint3 lookAtPos;						 // 0x08
			NiPointer<NiAVObject> lookAtObject;		 // 0x18
			NiPointer<NiLight> light;				 // 0x20
		};

		static_assert(sizeof(LightParams) == 0x28);

		static auto Create(
			const BSFixedString& a_name,
			UI_DEPTH_PRIORITY a_depth,
			REX::Float32 a_fov,
			bool a_alwaysRenderWhenEnabled) -> Renderer*
		{
			using FuncType = decltype(&Renderer::Create);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Create);
			return std::invoke(FUNC, a_name, a_depth, a_fov, a_alwaysRenderWhenEnabled);
		}

		[[nodiscard]]
		static auto GetByName(const BSFixedString& a_name) -> Renderer*
		{
			using FuncType = decltype(&Renderer::GetByName);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::GetByName);
			return std::invoke(FUNC, a_name);
		}

		void MainScreen_AddPointLight(
			NiPoint3 a_translation,
			NiColor a_diffuse,
			REX::Float32 a_radius,
			REX::Float32 a_dimmerVal)
		{
			using FuncType = decltype(&Renderer::MainScreen_AddPointLight);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::MainScreen_AddPointLight);
			std::invoke(FUNC, this, a_translation, a_diffuse, a_radius, a_dimmerVal);
		}

		void MainScreen_AddSpotLight(
			NiPoint3 a_translation,
			NiPoint3 a_lookAtPosition,
			NiAVObject* a_lookAtObject,
			REX::Float32 a_fov,
			NiColor a_diffuse,
			REX::Float32 a_radius,
			REX::Float32 a_dimmerVal,
			bool a_castShadows)
		{
			using FuncType = decltype(&Renderer::MainScreen_AddSpotLight);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::MainScreen_AddSpotLight);
			std::invoke(
				FUNC,
				this,
				a_translation,
				a_lookAtPosition,
				a_lookAtObject,
				a_fov,
				a_diffuse,
				a_radius,
				a_dimmerVal,
				a_castShadows);
		}

		void MainScreen_ClearLights()
		{
			using FuncType = decltype(&Renderer::MainScreen_ClearLights);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::MainScreen_ClearLights);
			std::invoke(FUNC, this);
		}

		void MainScreen_EnableAO(bool a_value)
		{
			enableAO = a_value;
		}

		void MainScreen_EnableScreenAttached3DMasking(const char* a_maskedGeomName, const char* a_maskedMaterialName)
		{
			maskedGeomName = a_maskedGeomName;
			maskedMaterialName = a_maskedMaterialName;
		}

		void MainScreen_RegisterGeometryRequiringFullViewport(NiAVObject* a_geometry)
		{
			elementRequiringFullVieport = a_geometry;
		}

		void MainScreen_SetBackgroundMode(BackgroundMode a_mode)
		{
			bgmode = a_mode;
		}

		void MainScreen_SetClearDepthStencil(bool a_clear)
		{
			clearDepthStencilMainScreen = a_clear;
		}

		void MainScreen_SetMenuBlendMode(OffscreenMenuBlendMode a_mode)
		{
			menuBlend = a_mode;
		}

		void MainScreen_SetMenuIntensity(REX::Float32 a_diffuse, REX::Float32 a_emit)
		{
			menuDiffuseIntensity = a_diffuse;
			menuEmitIntensity = a_emit;
		}

		void MainScreen_SetOpacityAlpha(REX::Float32 a_opacityAlpha)
		{
			opacityAlpha = a_opacityAlpha;
		}

		void MainScreen_SetPostAA(bool a_value)
		{
			postAA = a_value;
		}

		void MainScreen_SetScreenAttached3D(NiAVObject* a_root3D)
		{
			using FuncType = decltype(&Renderer::MainScreen_SetScreenAttached3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::MainScreen_SetScreenAttached3D);
			std::invoke(FUNC, this, a_root3D);
		}

		void MainScreen_SetUseDeferredRenderer(bool a_value)
		{
			defRenderMainScreen = a_value;
		}

		void MainScreen_SetWorldAttached3D(NiAVObject* a_root3D)
		{
			using FuncType = decltype(&Renderer::MainScreen_SetWorldAttached3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::MainScreen_SetWorldAttached3D);
			std::invoke(FUNC, this, a_root3D);
		}

		void MainScreen_SetWorldAttachedMenuIntensity(REX::Float32 a_diffuse, REX::Float32 a_emit)
		{
			menuDiffuseIntensityWA = a_diffuse;
			menuEmitIntensityWA = a_emit;
		}

		void MainScreen_SetHideScreenWhenDisabled(bool a_value)
		{
			hideScreenWhenDisabled = a_value;
		}

		void Offscreen_AddLight(NiPoint3 a_translation, NiColor a_diffuse, NiColor a_specular, REX::Float32 a_dimmerVal)
		{
			using FuncType = decltype(&Renderer::Offscreen_AddLight);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_AddLight);
			std::invoke(FUNC, this, a_translation, a_diffuse, a_specular, a_dimmerVal);
		}

		void Offscreen_Clear3D()
		{
			using FuncType = decltype(&Renderer::Offscreen_Clear3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_Clear3D);
			std::invoke(FUNC, this);
		}

		void Offscreen_ClearLights()
		{
			using FuncType = decltype(&Renderer::Offscreen_ClearLights);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_ClearLights);
			std::invoke(FUNC, this);
		}

		void Offscreen_Enable3D(bool a_value)
		{
			offscreen3DEnabled = a_value;
		}

		auto Offscreen_GetRenderTargetHeight() -> std::uint32_t
		{
			using FuncType = decltype(&Renderer::Offscreen_GetRenderTargetHeight);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_GetRenderTargetHeight);
			return std::invoke(FUNC, this);
		}

		auto Offscreen_GetRenderTargetWidth() -> std::uint32_t
		{
			using FuncType = decltype(&Renderer::Offscreen_GetRenderTargetWidth);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_GetRenderTargetWidth);
			return std::invoke(FUNC, this);
		}

		void Offscreen_Set3D(NiAVObject* a_3D)
		{
			using FuncType = decltype(&Renderer::Offscreen_Set3D);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_Set3D);
			std::invoke(FUNC, this, a_3D);
		}

		void Offscreen_SetBackgroundColor(const NiColorA& a_color)
		{
			clearColor = a_color;
		}

		void Offscreen_SetClearDepthStencil(bool a_clear)
		{
			clearDepthStencilOffscreen = a_clear;
		}

		void Offscreen_SetClearRenderTarget(bool a_clear)
		{
			clearRenderTarget = a_clear;
		}

		void Offscreen_SetDebugMode(bool a_on, bool a_small, std::uint32_t a_target)
		{
			using FuncType = decltype(&Renderer::Offscreen_SetDebugMode);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_SetDebugMode);
			std::invoke(FUNC, this, a_on, a_small, a_target);
		}

		void Offscreen_SetDirectionalLight(
			REX::Float32 a_xyPlaneAngle,
			REX::Float32 a_zAngle,
			NiColor a_diffuse,
			REX::Float32 a_dimmerVal)
		{
			using FuncType = decltype(&Renderer::Offscreen_SetDirectionalLight);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Offscreen_SetDirectionalLight);
			std::invoke(FUNC, this, a_xyPlaneAngle, a_zAngle, a_diffuse, a_dimmerVal);
		}

		void Offscreen_SetDisplayMode(ScreenMode a_mode, const char* a_screenGeomName, const char* a_screenMaterialName)
		{
			screenmode = a_mode;
			screenGeomName = a_screenGeomName;
			screenMaterialName = a_screenMaterialName;
		}

		void Offscreen_SetPostEffect(PostEffect a_effect)
		{
			postfx = a_effect;
		}

		void Offscreen_SetRenderTargetSize(OffscreenMenuSize a_size)
		{
			omsize = a_size;
		}

		void Offscreen_SetUseLongRangeCamera(bool a_use)
		{
			useLongRangeCamera = a_use;
		}

		void Enable(bool a_unhideGeometries = false)
		{
			using FuncType = decltype(&Renderer::Enable);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Enable);
			std::invoke(FUNC, this, a_unhideGeometries);
		}

		void Disable()
		{
			using FuncType = decltype(&Renderer::Disable);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Disable);
			std::invoke(FUNC, this);
		}

		static void DisableAll(bool a_disableAll)
		{
			using FuncType = decltype(&Renderer::DisableAll);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::DisableAll);
			std::invoke(FUNC, a_disableAll);
		}

		void Release()
		{
			using FuncType = decltype(&Renderer::Release);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::Release);
			std::invoke(FUNC, this);
		}

		void SetViewport(Scaleform::GFx::Movie& a_ui, const NiRectF& a_renderArea)
		{
			using FuncType = decltype(&Renderer::SetViewport);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Interface3D::SetViewport);
			std::invoke(FUNC, this, a_ui, a_renderArea);
		}

		// members
		BSTAlignedArray<UIShaderFXInfo> colorFXInfos;			   // 0x000
		BSTAlignedArray<UIShaderFXInfo> backgroundFXInfos;		   // 0x018
		mutable BSReadWriteLock cachedQuadsLock;				   // 0x030
		NiColorA clearColor;									   // 0x038
		REX::Float32 opacityAlpha;								   // 0x048
		bool enabled;											   // 0x04C
		bool offscreen3DEnabled;								   // 0x04D
		bool hideScreenWhenDisabled;							   // 0x04E
		bool usePremultAlpha;									   // 0x04F
		bool clearRenderTarget;									   // 0x050
		bool clearDepthStencilMainScreen;						   // 0x051
		bool clearDepthStencilOffscreen;						   // 0x052
		bool postAA;											   // 0x053
		bool useFullPremultAlpha;								   // 0x054
		bool alwaysRenderWhenEnabled;							   // 0x055
		bool defRenderMainScreen;								   // 0x056
		bool enableAO;											   // 0x057
		bool useLongRangeCamera;								   // 0x058
		bool needsLightSetup;									   // 0x059
		bool needsLightSetupOffscreen;							   // 0x05A
		REX::Enum<BackgroundMode, std::int32_t> bgmode;			   // 0x05C
		REX::Enum<PostEffect, std::int32_t> postfx;				   // 0x060
		REX::Enum<HighlightEffect, std::int32_t> highlightfx;	   // 0x064
		REX::Enum<OffscreenMenuSize, std::int32_t> omsize;		   // 0x068
		REX::Enum<ScreenMode, std::int32_t> screenmode;			   // 0x06C
		REX::Enum<OffscreenMenuBlendMode, std::int32_t> menuBlend; // 0x070
		REX::Enum<UI_DEPTH_PRIORITY, std::int32_t> depth;		   // 0x074
		NiPointer<NiAVObject> worldAttachedElementRoot;			   // 0x078
		NiPointer<NiAVObject> screenAttachedElementRoot;		   // 0x080
		NiPointer<NiAVObject> offscreenElement;					   // 0x088
		BSTArray<NiPointer<BSGeometry>> displayGeometry;		   // 0x090
		NiAVObject* elementRequiringFullVieport;				   // 0x0A8
		NiAVObject* highlightedElement;							   // 0x0B0
		bool highlightOffscreen;								   // 0x0B8
		OldScreenEffectControl pipfx;							   // 0x0BC
		OldScreenEffectControl vatsfx;							   // 0x12C
		NiPointer<BSShaderAccumulator> accum;					   // 0x1A0
		NiPointer<NiCamera> pipboyAspect;						   // 0x1A8
		NiPointer<NiCamera> nativeAspect;						   // 0x1B0
		NiPointer<NiCamera> nativeAspectLongRange;				   // 0x1B8
		std::int32_t customRenderTarget;						   // 0x1C0
		std::int32_t customSwapTarget;							   // 0x1C4
		BSTArray<LightParams> mainLights;						   // 0x1C8
		BSTArray<LightParams> offscreenLights;					   // 0x1E0
		REX::Float32 menuDiffuseIntensity;						   // 0x1F8
		REX::Float32 menuEmitIntensity;							   // 0x1FC
		REX::Float32 menuDiffuseIntensityWA;					   // 0x200
		REX::Float32 menuEmitIntensityWA;						   // 0x204
		BSFixedString name;										   // 0x208
		BSFixedString screenGeomName;							   // 0x210
		BSFixedString screenMaterialName;						   // 0x218
		BSFixedString maskedGeomName;							   // 0x220
		BSFixedString maskedMaterialName;						   // 0x228
		NiDirectionalLight* directionalLight;					   // 0x230
		NiPointer<ShadowSceneNode> screenSSN;					   // 0x238
		NiPointer<ShadowSceneNode> offscreenSSN;				   // 0x240
	};

	static_assert(sizeof(Renderer) == 0x248);
}
