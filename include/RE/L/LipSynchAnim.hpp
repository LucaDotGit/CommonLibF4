#pragma once

#include "RE/B/BSExternalAudioIO_ExternalLoad.hpp"

namespace RE
{
	class LipSynchAnim
	{
	public:
		// members
		std::uint32_t numFrames{ 0 };			   // 00
		std::int32_t startingFrame{ 0 };		   // 04
		std::uint32_t numPhonemeTargets{ 0 };	   // 08
		REX::Float32** phonemes01{ nullptr };	   // 10
		REX::Float32** modifiers{ nullptr };	   // 18
		REX::Float32* phonemes02{ nullptr };	   // 20
		bool hasGestures{ false };				   // 28
		std::uint32_t versionNumber{ 0 };		   // 2C
		BSExternalAudioIO::ExternalLoad voiceData; // 30;
	};
	static_assert(sizeof(LipSynchAnim) == 0x48);
}
