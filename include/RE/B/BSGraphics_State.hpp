#pragma once

#include "RE/B/BSGraphics_CameraStateData.hpp"
#include "RE/B/BSGraphics_FogStateType.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiRect.hpp"

namespace RE
{
	class NiTexture;
	class Texture;
}

namespace RE::BSGraphics
{
	enum class MultiSampleLevel : std::int32_t;
	enum class TAA_STATE : std::int32_t;

	class State
	{
	public:
		[[nodiscard]] static State& GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<State*>{ ID::BSGraphics::State::Singleton };
			return *SINGLETON;
		}

		// members
		std::uint32_t currentFrame;							   // 000
		REX::Float32 offsetX;								   // 004
		REX::Float32 offsetY;								   // 008
		std::uint32_t currentFrameOffset;					   // 00C
		std::uint32_t previousFrameOffset;					   // 010
		FogStateType fogState;								   // 014
		REX::Enum<MultiSampleLevel, std::int32_t> multiSample; // 074
		std::uint32_t backBufferWidth;						   // 078
		std::uint32_t backBufferHeight;						   // 07C
		std::uint32_t screenWidth;							   // 080
		std::uint32_t screenHeight;							   // 084
		NiRect<REX::Float32> frameBufferViewport;			   // 088
		std::uint32_t frameCount;							   // 098
		std::uint32_t frameID;								   // 09C
		bool insideFrame;									   // 0A0
		bool letterbox;										   // 0A1
		bool allowDepthBufferAsTexture;						   // 0A2
		bool shadows;										   // 0A3
		bool compiledShaderThisFrame;						   // 0A4
		REX::Enum<TAA_STATE, std::int32_t> taaState;		   // 0A8
		std::uint32_t taaDisableCounter;					   // 0AC
		std::uint32_t trijuiceState;						   // 0B0
		NiPointer<NiTexture> defaultTextureBlack;			   // 0B8
		NiPointer<NiTexture> defaultTextureWhite;			   // 0C0
		NiPointer<NiTexture> defaultTextureGrey;			   // 0C8
		NiPointer<NiTexture> defaultHeightMap;				   // 0D0
		NiPointer<NiTexture> defaultReflectionCubeMap;		   // 0D8
		NiPointer<NiTexture> defaultFaceDetailMap;			   // 0E0
		NiPointer<NiTexture> defaultHighFreqNormalMap;		   // 0E8
		NiPointer<NiTexture> defaultTexEffectMap;			   // 0F0
		NiPointer<NiTexture> defaultTextureWhiteNoiseMap;	   // 0F8
		NiPointer<NiTexture> defaultTextureWhiteNoiseMapSmall; // 100
		NiPointer<NiTexture> defaultTextureNormalMap;		   // 108
		NiPointer<NiTexture> defaultTextureDiffuseMap;		   // 110
		NiPointer<NiTexture> defaultSplineMap;				   // 118
		NiPointer<NiTexture> defaultTextureDissolvePattern;	   // 120
		Texture* defaultImagespaceLUT;						   // 128
		NiPointer<NiTexture> rotatedPoissonDiscLookupMap;	   // 130
		std::uint32_t presentImmediateThreshold;			   // 138
		std::uint32_t presentFlag;							   // 13C
		BSTArray<CameraStateData> cameraDataCache;			   // 140
		CameraStateData cameraState;						   // 160
		bool commitTexturesOnCreation;						   // 3B0
		bool immediateTextureLoads;							   // 3B1
	};
	static_assert(sizeof(State) == 0x3C0);
}
