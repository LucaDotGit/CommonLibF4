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
		[[nodiscard]]
		static auto GetSingleton() noexcept -> State*
		{
			static const auto SINGLETON = REL::Relocation<State*>(ID::BSGraphics::State::Singleton);
			return SINGLETON.get();
		}

		// members
		std::uint32_t currentFrame;							   // 0x000
		REX::Float32 offsetX;								   // 0x004
		REX::Float32 offsetY;								   // 0x008
		std::uint32_t currentFrameOffset;					   // 0x00C
		std::uint32_t previousFrameOffset;					   // 0x010
		FogStateType fogState;								   // 0x014
		REX::Enum<MultiSampleLevel, std::int32_t> multiSample; // 0x074
		std::uint32_t backBufferWidth;						   // 0x078
		std::uint32_t backBufferHeight;						   // 0x07C
		std::uint32_t screenWidth;							   // 0x080
		std::uint32_t screenHeight;							   // 0x084
		NiRectF frameBufferViewport;						   // 0x088
		std::uint32_t frameCount;							   // 0x098
		std::uint32_t frameID;								   // 0x09C
		bool insideFrame;									   // 0x0A0
		bool letterbox;										   // 0x0A1
		bool allowDepthBufferAsTexture;						   // 0x0A2
		bool shadows;										   // 0x0A3
		bool compiledShaderThisFrame;						   // 0x0A4
		REX::Enum<TAA_STATE, std::int32_t> taaState;		   // 0x0A8
		std::uint32_t taaDisableCounter;					   // 0x0AC
		std::uint32_t trijuiceState;						   // 0x0B0
		NiPointer<NiTexture> defaultTextureBlack;			   // 0x0B8
		NiPointer<NiTexture> defaultTextureWhite;			   // 0x0C0
		NiPointer<NiTexture> defaultTextureGrey;			   // 0x0C8
		NiPointer<NiTexture> defaultHeightMap;				   // 0x0D0
		NiPointer<NiTexture> defaultReflectionCubeMap;		   // 0x0D8
		NiPointer<NiTexture> defaultFaceDetailMap;			   // 0x0E0
		NiPointer<NiTexture> defaultHighFreqNormalMap;		   // 0x0E8
		NiPointer<NiTexture> defaultTexEffectMap;			   // 0x0F0
		NiPointer<NiTexture> defaultTextureWhiteNoiseMap;	   // 0x0F8
		NiPointer<NiTexture> defaultTextureWhiteNoiseMapSmall; // 0x100
		NiPointer<NiTexture> defaultTextureNormalMap;		   // 0x108
		NiPointer<NiTexture> defaultTextureDiffuseMap;		   // 0x110
		NiPointer<NiTexture> defaultSplineMap;				   // 0x118
		NiPointer<NiTexture> defaultTextureDissolvePattern;	   // 0x120
		Texture* defaultImagespaceLUT;						   // 0x128
		NiPointer<NiTexture> rotatedPoissonDiscLookupMap;	   // 0x130
		std::uint32_t presentImmediateThreshold;			   // 0x138
		std::uint32_t presentFlag;							   // 0x13C
		BSTArray<CameraStateData> cameraDataCache;			   // 0x140
		CameraStateData cameraState;						   // 0x160
		bool commitTexturesOnCreation;						   // 0x3B0
		bool immediateTextureLoads;							   // 0x3B1
	};

	static_assert(sizeof(State) == 0x3C0);
}
