#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	inline constexpr auto XAUDIO2FX_REVERB_MIN_WET_DRY_MIX = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_REFLECTIONS_DELAY = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_REVERB_DELAY = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_REAR_DELAY = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_POSITION = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_DIFFUSION = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_LOW_EQ_GAIN = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_LOW_EQ_CUTOFF = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_HIGH_EQ_GAIN = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_HIGH_EQ_CUTOFF = static_cast<std::uint32_t>(0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_ROOM_FILTER_FREQ = static_cast<REX::Float32>(20.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_ROOM_FILTER_MAIN = static_cast<REX::Float32>(-100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_ROOM_FILTER_HF = static_cast<REX::Float32>(-100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_REFLECTIONS_GAIN = static_cast<REX::Float32>(-100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_REVERB_GAIN = static_cast<REX::Float32>(-100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_DECAY_TIME = static_cast<REX::Float32>(0.1);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_DENSITY = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_MIN_ROOM_SIZE = static_cast<REX::Float32>(0.0);

	inline constexpr auto XAUDIO2FX_REVERB_MAX_WET_DRY_MIX = static_cast<REX::Float32>(100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_REFLECTIONS_DELAY = static_cast<std::uint32_t>(300);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_REVERB_DELAY = static_cast<std::uint32_t>(85);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_REAR_DELAY = static_cast<std::uint32_t>(5);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_POSITION = static_cast<std::uint32_t>(30);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_DIFFUSION = static_cast<std::uint32_t>(15);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_LOW_EQ_GAIN = static_cast<std::uint32_t>(12);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_LOW_EQ_CUTOFF = static_cast<std::uint32_t>(9);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_HIGH_EQ_GAIN = static_cast<std::uint32_t>(8);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_HIGH_EQ_CUTOFF = static_cast<std::uint32_t>(14);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_ROOM_FILTER_FREQ = static_cast<REX::Float32>(20000.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_ROOM_FILTER_MAIN = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_ROOM_FILTER_HF = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_REFLECTIONS_GAIN = static_cast<REX::Float32>(20.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_REVERB_GAIN = static_cast<REX::Float32>(20.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_DENSITY = static_cast<REX::Float32>(100.0);
	inline constexpr auto XAUDIO2FX_REVERB_MAX_ROOM_SIZE = static_cast<REX::Float32>(100.0);

	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_WET_DRY_MIX = static_cast<REX::Float32>(100.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_DELAY = static_cast<std::uint32_t>(5);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_REVERB_DELAY = static_cast<std::uint32_t>(5);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_REAR_DELAY = static_cast<std::uint32_t>(5);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_POSITION = static_cast<std::uint32_t>(6);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_POSITION_MATRIX = static_cast<std::uint32_t>(27);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_EARLY_DIFFUSION = static_cast<std::uint32_t>(8);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_LATE_DIFFUSION = static_cast<std::uint32_t>(8);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_GAIN = static_cast<std::uint32_t>(8);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_LOW_EQ_CUTOFF = static_cast<std::uint32_t>(4);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_GAIN = static_cast<std::uint32_t>(8);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_HIGH_EQ_CUTOFF = static_cast<std::uint32_t>(4);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_FREQ = static_cast<REX::Float32>(5000.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_MAIN = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_ROOM_FILTER_HF = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_REFLECTIONS_GAIN = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_REVERB_GAIN = static_cast<REX::Float32>(0.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_DECAY_TIME = static_cast<REX::Float32>(1.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_DENSITY = static_cast<REX::Float32>(100.0);
	inline constexpr auto XAUDIO2FX_REVERB_DEFAULT_ROOM_SIZE = static_cast<REX::Float32>(100.0);
}

namespace REX::W32
{
	struct XAUDIO2FX_REVERB_I3DL2_PARAMETERS
	{
		REX::Float32 wetDryMix;
		std::int32_t room;
		std::int32_t roomHF;
		REX::Float32 roomRolloffFactor;
		REX::Float32 decayTime;
		REX::Float32 decayHFRatio;
		std::int32_t reflections;
		REX::Float32 reflectionsDelay;
		std::int32_t reverb;
		REX::Float32 reverbDelay;
		REX::Float32 diffusion;
		REX::Float32 density;
		REX::Float32 hfReference;
	};

	struct XAUDIO2FX_REVERB_PARAMETERS
	{
		REX::Float32 wetDryMix;
		std::uint32_t reflectionsDelay;
		std::uint8_t reverbDelay;
		std::uint8_t rearDelay;
		std::uint8_t positionLeft;
		std::uint8_t positionRight;
		std::uint8_t positionMatrixLeft;
		std::uint8_t positionMatrixRight;
		std::uint8_t earlyDiffusion;
		std::uint8_t lateDiffusion;
		std::uint8_t lowEQGain;
		std::uint8_t lowEQCutoff;
		std::uint8_t highEQGain;
		std::uint8_t highEQCutoff;
		REX::Float32 roomFilterFreq;
		REX::Float32 roomFilterMain;
		REX::Float32 roomFilterHF;
		REX::Float32 reflectionsGain;
		REX::Float32 reverbGain;
		REX::Float32 decayTime;
		REX::Float32 density;
		REX::Float32 roomSize;
	};
}

namespace REX::W32
{
	inline constexpr auto XAUDIO2FX_I3DL2_PRESET_DEFAULT = XAUDIO2FX_REVERB_I3DL2_PARAMETERS{
		.wetDryMix = static_cast<REX::Float32>(100.0),
		.room = -10'000,
		.roomHF = 0,
		.roomRolloffFactor = static_cast<REX::Float32>(0.0),
		.decayTime = static_cast<REX::Float32>(1.0),
		.decayHFRatio = static_cast<REX::Float32>(0.5),
		.reflections = -10'000,
		.reflectionsDelay = static_cast<REX::Float32>(0.02),
		.reverb = -10'000,
		.reverbDelay = static_cast<REX::Float32>(0.04),
		.diffusion = static_cast<REX::Float32>(100.0),
		.density = static_cast<REX::Float32>(100.0),
		.hfReference = static_cast<REX::Float32>(5000.0)
	};
}
