#pragma once

#include "REX/W32/CORE.hpp"
#include "REX/W32/D3D.hpp"

namespace REX::W32
{
	inline constexpr auto X3DAUDIO_HANDLE_BYTESIZE = static_cast<std::uint32_t>(20);

	inline constexpr auto X3DAUDIO_SPEED_OF_SOUND = static_cast<REX::Float32>(343.5);

	inline constexpr auto X3DAUDIO_CALCULATE_MATRIX = static_cast<std::uint32_t>(0x01);
	inline constexpr auto X3DAUDIO_CALCULATE_DELAY = static_cast<std::uint32_t>(0x02);
	inline constexpr auto X3DAUDIO_CALCULATE_LPF_DIRECT = static_cast<std::uint32_t>(0x04);
	inline constexpr auto X3DAUDIO_CALCULATE_LPF_REVERB = static_cast<std::uint32_t>(0x08);
	inline constexpr auto X3DAUDIO_CALCULATE_REVERB = static_cast<std::uint32_t>(0x10);
	inline constexpr auto X3DAUDIO_CALCULATE_DOPPLER = static_cast<std::uint32_t>(0x20);
	inline constexpr auto X3DAUDIO_CALCULATE_EMITTER_ANGLE = static_cast<std::uint32_t>(0x40);
	inline constexpr auto X3DAUDIO_CALCULATE_ZEROCENTER = static_cast<std::uint32_t>(0x1'0000);
	inline constexpr auto X3DAUDIO_CALCULATE_REDIRECT_TO_LFE = static_cast<std::uint32_t>(0x2'0000);
}

namespace REX::W32
{
	using X3DAUDIO_HANDLE = std::array<std::uint8_t, X3DAUDIO_HANDLE_BYTESIZE>;
	using X3DAUDIO_VECTOR = XMFLOAT3;

	struct X3DAUDIO_CONE
	{
		REX::Float32 innerAngle;
		REX::Float32 outerAngle;
		REX::Float32 innerVolume;
		REX::Float32 outerVolume;
		REX::Float32 innerLPF;
		REX::Float32 outerLPF;
		REX::Float32 innerReverb;
		REX::Float32 outerReverb;
	};

	struct X3DAUDIO_DISTANCE_CURVE_POINT
	{
		REX::Float32 distance;
		REX::Float32 dspSetting;
	};

	struct X3DAUDIO_DISTANCE_CURVE
	{
		X3DAUDIO_DISTANCE_CURVE_POINT* points;
		std::uint32_t pointCount;
	};

	struct X3DAUDIO_DSP_SETTINGS
	{
		REX::Float32* matrixCoefficients;
		REX::Float32* delayTimes;
		std::uint32_t srcChannelCount;
		std::uint32_t dstChannelCount;
		REX::Float32 lpfDirectCoefficient;
		REX::Float32 lpfReverbCoefficient;
		REX::Float32 reverbLevel;
		REX::Float32 dopplerFactor;
		REX::Float32 emitterToListenerAngle;
		REX::Float32 emitterToListenerDistance;
		REX::Float32 emitterVelocityComponent;
		REX::Float32 listenerVelocityComponent;
	};

	struct X3DAUDIO_EMITTER
	{
		X3DAUDIO_CONE* cone;
		X3DAUDIO_VECTOR orientFront;
		X3DAUDIO_VECTOR orientTop;
		X3DAUDIO_VECTOR position;
		X3DAUDIO_VECTOR velocity;
		REX::Float32 innerRadius;
		REX::Float32 innerRadiusAngle;
		std::uint32_t channelCount;
		REX::Float32 channelRadius;
		REX::Float32* channelAzimuths;
		X3DAUDIO_DISTANCE_CURVE* volumeCurve;
		X3DAUDIO_DISTANCE_CURVE* lfeCurve;
		X3DAUDIO_DISTANCE_CURVE* lpfDirectCurve;
		X3DAUDIO_DISTANCE_CURVE* lpfReverbCurve;
		X3DAUDIO_DISTANCE_CURVE* reverbCurve;
		REX::Float32 curveDistanceScaler;
		REX::Float32 dopplerScaler;
	};

	struct X3DAUDIO_LISTENER
	{
		X3DAUDIO_VECTOR orientFront;
		X3DAUDIO_VECTOR orientTop;
		X3DAUDIO_VECTOR position;
		X3DAUDIO_VECTOR velocity;
		X3DAUDIO_CONE* cone;
	};
}
