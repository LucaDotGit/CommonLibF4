#pragma once

#include "RE/B/BSGeometry.hpp"
#include "RE/N/NiColorA.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiTexture.hpp"
#include "RE/N/NiTransform.hpp"

namespace RE
{
	class ShadowSceneNode;

	class BSShaderManager
	{
	public:
		enum class BSShaderTimerMode : std::int32_t
		{
			Default = 0,
			Delta = 1,
			System = 2,
			RealDelta = 3,
			FrameCount = 4,
			AccumulatedDelta = 5,

			_Count = 6
		};

		enum class ShaderEnum : std::int32_t
		{
			Effect = 0,
			Utility = 1,
			DistantTree = 2,
			Particle = 3,
			DFPrepass = 4,
			DFLight = 5,
			DFComposite = 6,
			Sky = 7,
			Lighting = 8,
			BloodSpatter = 9,
			Water = 10,
			FaceCustomization = 11,
			ImageSpace = 12,

			_Count = 13
		};

		enum class CameraInWaterState : std::int32_t
		{
			AboveWater = 0,
			PartiallyAboveWater = 1,
			PartiallyUnderWater = 2,
			UnderWater = 3
		};

		enum class SceneGraphEnum : std::int32_t
		{
			World = 0,
			UIOld = 1,
			Preview = 2,
			UILoadingMenu = 3,
			UI = 4,

			_Count = 5
		};

		enum class RenderFlags : std::uint32_t
		{
			ColorWriteDisable = 0
		};

		enum class RenderMode : std::int32_t
		{
			Normal = 0,
			NumLights = 1,
			NumNonShadowLights = 2,
			NumShadowLights = 3,
			NumPasses = 4,
			SinglePass = 5,
			TexUsage = 6,
			Degrade = 7,
			Fade = 8,
			ShadowSplitDebug = 9,
			TexSize = 10,
			FadeNodeTriDebug = 11,
			Overdraw = 12,
			DepthPrepass = 13,
			OcclusionMap = 14,
			Shadowmap = 15,
			ShadowmapDir = 16,
			ShadowmapPB = 17,
			Localmap = 18,
			Frozen = 19,
			ScreenSplatter = 20,
			LODOnlyNoNoise = 21,
			SilhouetteLOD = 22,
			Silhouette = 23,
			DeferredGBuffer = 24,
			DeferredGB0 = 25,
			DeferredGBDebgStart = 25,
			DeferredGB1 = 26,
			DeferredGB2 = 27,
			DeferredGB3 = 28,
			DeferredGB4 = 29,
			DeferredGB5 = 30,
			DeferredGBDebugEnd = 30,
			DeferredGBAll = 31,
			Lightvis = 32,
			VATSMask = 33,
			VATSMaskDebug = 34,
			VATSMaskPrepass = 35,
			MapMaker = 37,
			SimpleLighting = 38,

			_Count = 39
		};

		enum class ShadowMode : std::int32_t
		{
			ISFilter = 0,
			PCF4 = 1,
			PCF9 = 2,
			LoopFilter = 3
		};

		class State
		{
		public:
			// members
			std::array<ShadowSceneNode*, 5> shadowSceneNode; // 0x00
			std::array<REX::Float32, 6> timerValues;		 // 0x28
			std::uint32_t frameCount;						 // 0x40
			NiColorA loadedRange;							 // 0x44
			bool interior;									 // 0x54
			bool liteBright;								 // 0x55
			bool deferredRGBEmit;							 // 0x56
			bool deferredRGBSpec;							 // 0x57
			bool menuScreenPremultAlpha;					 // 0x58
			bool menuScreenPostAA;							 // 0x59
			REX::Float32 menuScreenAlpha;					 // 0x5C
			bool characterLightEnabled;						 // 0x60
			bool screenSpaceReflectionsEnabled;				 // 0x61
			bool screenSpaceSubsurfaceScatteringEnabled;	 // 0x62
			std::uint32_t pipboyScreenTarget;				 // 0x64
			NiPointer<NiTexture> pipboyFXTexture;			 // 0x68
			REX::Float32 pipboyScreenEmitIntensity;			 // 0x70
			REX::Float32 pipboyScreenDiffuseIntensity;		 // 0x74
			REX::Float32 pipboyScreenEmitIntensityWA;		 // 0x78
			REX::Float32 pipboyScreenDiffuseIntensityWA;	 // 0x7C
			REX::Float32 specularLODStartFadeSquared;		 // 0x80
			REX::Float32 specularLODEndSquared;				 // 0x84
			REX::Float32 landLOFaceSeconds;					 // 0x88
			REX::Float32 leafAnimDampenDistStartSPU;		 // 0x8C
			REX::Float32 leafAnimDampenDistEndSPU;			 // 0x90
			NiPoint2 oldGridArrayCenter;					 // 0x94
			NiPoint2 gridArrayCenter;						 // 0x9C
			REX::Float32 gridArrayLerpStart;				 // 0xA4
			bool LODFadeInProgress;							 // 0xA8
			std::uint8_t sceneGraph;						 // 0xA9
			REX::Enum<RenderMode, std::int32_t> debugMode;	 // 0xAC
			std::uint32_t debugColorWrite;					 // 0xB0
			NiTransform directionalAmbientTransform;		 // 0xC0
			NiTransform localDirectionalAmbientTransform;	 // 0x100
			NiColorA ambientSpecular;						 // 0x140
			bool ambientSpecularEnabled;					 // 0x150
			std::uint32_t textureTransformCurrentBuffer;	 // 0x154
			std::uint32_t textureTransformFlipMode;			 // 0x158
			std::uint32_t cameraInWaterState;				 // 0x15C
			REX::Float32 cameraNear;						 // 0x160
			REX::Float32 cameraFar;							 // 0x164
			REX::Float32 waterIntersect;					 // 0x168
			NiColorA menuScreenBlendParams;					 // 0x16C
			NiColorA debugTintColor;						 // 0x17C
			REX::Float32 boneTintingTiming;					 // 0x18C
			NiPoint3 forwardLightOffset;					 // 0x190
			std::array<NiPoint3, 2> clipVolume;				 // 0x19C
			NiPointer<BSGeometry> clipVolumeGeom;			 // 0x1B8
			NiColorA maskRectParams;						 // 0x1C0
			std::array<NiColorA, 16> UIMaskRectsA;			 // 0x1D0
			std::array<NiColorA, 16> UIMaskRectColorsA;		 // 0x2D0
			NiColorA characterLightParams;					 // 0x3D0
			std::uint32_t forceDisableFrame;				 // 0x3E0
			bool effectShaderVATSHighlight;					 // 0x3E4
			bool forceEffectShaderPremultAlpha;				 // 0x3E5
			bool forceDisableSSR;							 // 0x3E6
			bool forceDisableGodrays;						 // 0x3E7
			bool forceDisableDirLights;						 // 0x3E8
			bool pendingForceDisableSSR;					 // 0x3E9
			bool pendingForceDisableGodrays;				 // 0x3EA
			bool pendingForceDisableDirLights;				 // 0x3EB
		};

		static_assert(sizeof(State) == 0x3F0);
	};
}
