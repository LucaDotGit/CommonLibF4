#pragma once

#include "RE/B/BSAudioCallbacks.hpp"
#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class BSAudioInit
	{
	public:
		// members
		BSAudioCallbacks audioCallbacks;	 // 00
		BSFixedString systemName;			 // 18
		BSFixedString missingAssetSoundFile; // 20
		void* extIOInterface;				 // 28 - TODO: `BSExternalAudioIO::ExternalIOInterface`
		std::uint32_t initialCacheSize;		 // 30
		std::uint32_t maxAudioCacheSize;	 // 34
		std::uint32_t maxSizeForCachedSound; // 38
		std::uint32_t audioHWThread;		 // 3C
		std::uint32_t streamingThreshold;	 // 40
		REX::Float32 defaultMasterVolume;	 // 44
		bool runDisabled;					 // 48
		bool enableAudioCache;				 // 49
		bool enableAsyncLoads;				 // 4A
	};
	static_assert(sizeof(BSAudioInit) == 0x50);
}
