#pragma once

#include "RE/B/BSGeometry.hpp"
#include "RE/N/NiColor.hpp"
#include "RE/N/NiPoint.hpp"
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
			kDefault = 0,
			kDelta = 1,
			kSystem = 2,
			kRealDelta = 3,
			kFrameCount = 4,
			kAccumulatedDelta = 5,

			kTotal = 6
		};

		enum class ShaderEnum : std::int32_t
		{
			kEffect = 0,
			kUtility = 1,
			kDistantTree = 2,
			kParticle = 3,
			kDFPrepass = 4,
			kDFLight = 5,
			kDFComposite = 6,
			kSky = 7,
			kLighting = 8,
			kBloodSpatter = 9,
			kWater = 10,
			kFaceCustomization = 11,
			kImageSpace = 12,

			kTotal = 13
		};

		enum class CameraInWaterState : std::int32_t
		{
			kAboveWater = 0,
			kPartiallyAboveWater = 1,
			kPartiallyUnderWater = 2,
			kUnderWater = 3
		};

		enum class SceneGraphEnum : std::int32_t
		{
			kWorld = 0,
			kUIOld = 1,
			kPreview = 2,
			kUILoadingMenu = 3,
			kUI = 4,

			kTotal = 5
		};

		enum class RenderFlags : std::uint32_t
		{
			kColorWriteDisable = 0
		};

		enum class RenderMode : std::int32_t
		{
			kNormal = 0,
			kNumLights = 1,
			kNumNonShadowLights = 2,
			kNumShadowLights = 3,
			kNumPasses = 4,
			kSinglePass = 5,
			kTexUsage = 6,
			kDegrade = 7,
			kFade = 8,
			kShadowSplitDebug = 9,
			kTexSize = 10,
			kFadeNodeTriDebug = 11,
			kOverdraw = 12,
			kDepthPrepass = 13,
			kOcclusionMap = 14,
			kShadowmap = 15,
			kShadowmapDir = 16,
			kShadowmapPB = 17,
			kLocalmap = 18,
			kFrozen = 19,
			kScreenSplatter = 20,
			kLODOnlyNoNoise = 21,
			kSilhouetteLOD = 22,
			kSilhouette = 23,
			kDeferredGBuffer = 24,
			kDeferredGB0 = 25,
			kDeferredGBDebgStart = 25,
			kDeferredGB1 = 26,
			kDeferredGB2 = 27,
			kDeferredGB3 = 28,
			kDeferredGB4 = 29,
			kDeferredGB5 = 30,
			kDeferredGBDebugEnd = 30,
			kDeferredGBAll = 31,
			kLightvis = 32,
			kVATSMask = 33,
			kVATSMaskDebug = 34,
			kVATSMaskPrepass = 35,
			kMapMaker = 37,
			kSimpleLighting = 38,

			kTotal = 39
		};

		enum class ShadowMode : std::int32_t
		{
			kISFilter = 0,
			kPCF4 = 1,
			kPCF9 = 2,
			kLoopFilter = 3
		};

		class State
		{
		public:
			// members
			std::array<ShadowSceneNode*, 5> shadowSceneNode; // 00
			std::array<REX::Float32, 6> timerValues;		 // 28
			std::uint32_t frameCount;						 // 40
			NiColorA loadedRange;							 // 44
			bool interior;									 // 54
			bool liteBright;								 // 55
			bool deferredRGBEmit;							 // 56
			bool deferredRGBSpec;							 // 57
			bool menuScreenPremultAlpha;					 // 58
			bool menuScreenPostAA;							 // 59
			REX::Float32 menuScreenAlpha;					 // 5C
			bool characterLightEnabled;						 // 60
			bool screenSpaceReflectionsEnabled;				 // 61
			bool screenSpaceSubsurfaceScatteringEnabled;	 // 62
			std::uint32_t pipboyScreenTarget;				 // 64
			NiPointer<NiTexture> pipboyFXTexture;			 // 68
			REX::Float32 pipboyScreenEmitIntensity;			 // 70
			REX::Float32 pipboyScreenDiffuseIntensity;		 // 74
			REX::Float32 pipboyScreenEmitIntensityWA;		 // 78
			REX::Float32 pipboyScreenDiffuseIntensityWA;	 // 7C
			REX::Float32 specularLODStartFadeSquared;		 // 80
			REX::Float32 specularLODEndSquared;				 // 84
			REX::Float32 landLOFaceSeconds;					 // 88
			REX::Float32 leafAnimDampenDistStartSPU;		 // 8C
			REX::Float32 leafAnimDampenDistEndSPU;			 // 90
			NiPoint2 oldGridArrayCenter;					 // 94
			NiPoint2 gridArrayCenter;						 // 9C
			REX::Float32 gridArrayLerpStart;				 // A4
			bool LODFadeInProgress;							 // A8
			std::uint8_t sceneGraph;						 // A9
			REX::Enum<RenderMode, std::int32_t> debugMode;	 // AC
			std::uint32_t debugColorWrite;					 // B0
			NiTransform directionalAmbientTransform;		 // C0
			NiTransform localDirectionalAmbientTransform;	 // 100
			NiColorA ambientSpecular;						 // 140
			bool ambientSpecularEnabled;					 // 150
			std::uint32_t textureTransformCurrentBuffer;	 // 154
			std::uint32_t textureTransformFlipMode;			 // 158
			std::uint32_t cameraInWaterState;				 // 15C
			REX::Float32 cameraNear;						 // 160
			REX::Float32 cameraFar;							 // 164
			REX::Float32 waterIntersect;					 // 168
			NiColorA menuScreenBlendParams;					 // 16C
			NiColorA debugTintColor;						 // 17C
			REX::Float32 boneTintingTiming;					 // 18C
			NiPoint3 forwardLightOffset;					 // 190
			std::array<NiPoint3, 2> clipVolume;				 // 19C
			NiPointer<BSGeometry> clipVolumeGeom;			 // 1B8
			NiColorA maskRectParams;						 // 1C0
			std::array<NiColorA, 16> UIMaskRectsA;			 // 1D0
			std::array<NiColorA, 16> UIMaskRectColorsA;		 // 2D0
			NiColorA characterLightParams;					 // 3D0
			std::uint32_t forceDisableFrame;				 // 3E0
			bool effectShaderVATSHighlight;					 // 3E4
			bool forceEffectShaderPremultAlpha;				 // 3E5
			bool forceDisableSSR;							 // 3E6
			bool forceDisableGodrays;						 // 3E7
			bool forceDisableDirLights;						 // 3E8
			bool pendingForceDisableSSR;					 // 3E9
			bool pendingForceDisableGodrays;				 // 3EA
			bool pendingForceDisableDirLights;				 // 3EB
		};
		static_assert(sizeof(State) == 0x3F0);
	};
}
