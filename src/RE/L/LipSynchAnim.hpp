#pragma once

#include "RE/B/BSExternalAudioIO_ExternalLoad.hpp"

namespace RE
{
	class LipSynchAnim
	{
	public:
		// members
		std::uint32_t numFrames{0};				   // 0x00
		std::int32_t startingFrame{0};			   // 0x04
		std::uint32_t numPhonemeTargets{0};		   // 0x08
		REX::Float32** phonemes01{nullptr};		   // 0x10
		REX::Float32** modifiers{nullptr};		   // 0x18
		REX::Float32* phonemes02{nullptr};		   // 0x20
		bool hasGestures{false};				   // 0x28
		std::uint32_t versionNumber{0};			   // 0x2C
		BSExternalAudioIO::ExternalLoad voiceData; // 0x30;
	};

	static_assert(sizeof(LipSynchAnim) == 0x48);
}
