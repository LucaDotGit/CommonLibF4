#pragma once

#include "RE/B/BSAudioCallbacks.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE::BSExternalAudioIO
{
	class ExternalIOInterface;
}

namespace RE
{
	class BSAudioInit
	{
	public:
		// members
		BSAudioCallbacks audioCallbacks;						// 0x00
		BSFixedString systemName;								// 0x18
		BSFixedString missingAssetSoundFile;					// 0x20
		BSExternalAudioIO::ExternalIOInterface* extIOInterface; // 0x28
		std::uint32_t initialCacheSize;							// 0x30
		std::uint32_t maxAudioCacheSize;						// 0x34
		std::uint32_t maxSizeForCachedSound;					// 0x38
		std::uint32_t audioHWThread;							// 0x3C
		std::uint32_t streamingThreshold;						// 0x40
		REX::Float32 defaultMasterVolume;						// 0x44
		bool runDisabled;										// 0x48
		bool enableAudioCache;									// 0x49
		bool enableAsyncLoads;									// 0x4A
	};

	static_assert(sizeof(BSAudioInit) == 0x50);
}
