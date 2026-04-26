#pragma once

#include "RE/B/BSAudioCallbacks.hpp"
#include "RE/B/BSAudioInit.hpp"
#include "RE/B/BSISoundDescriptor.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSSoundHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSAudioManagerThread;
	class BSGameSound;
	class BSISoundOutputModel;
	class BSMultisound;
	class BSSoundInfo;
	class NiAVObject;
	class SoundMessageList;
	class SoundMessageStack;

	class BSAudioManager
	{
	public:
		class SyncedPlaybackManager
		{
		public:
			// members
			BSTArray<BSTSmallArray<std::uint32_t, 2>*> syncFamilies; // 00
		};
		static_assert(sizeof(SyncedPlaybackManager) == 0x18);

		[[nodiscard]] static BSAudioManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BSAudioManager**>{ ID::BSAudioManager::Singleton };
			return *SINGLETON;
		}

		void GetSoundHandleByFile(BSSoundHandle& a_soundHandle, const BSResource::ID& a_file, std::uint32_t a_usageFlags, std::uint8_t a_priority)
		{
			using FuncType = decltype(&BSAudioManager::GetSoundHandleByFile);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSAudioManager::GetSoundHandleByFile };
			FUNC(this, a_soundHandle, a_file, a_usageFlags, a_priority);
		}

		void GetSoundHandleByName(BSSoundHandle& a_soundHandle, const char* a_soundName, REX::Float32 a_distance, std::uint32_t a_usageFlags, BSISoundDescriptor::ExtraResolutionData* a_data)
		{
			using FuncType = decltype(&BSAudioManager::GetSoundHandleByName);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BSAudioManager::GetSoundHandleByName };
			FUNC(this, a_soundHandle, a_soundName, a_distance, a_usageFlags, a_data);
		}

		// members
		std::int32_t messageListIndex;												  // 000
		std::int32_t messageProcessingListIndex;									  // 004
		std::array<SoundMessageList*, 2> messages;									  // 008
		SoundMessageStack* freeMessages;											  // 018
		SoundMessageStack* garbageMessages;											  // 020
		BSTHashMap<std::uint32_t, BSGameSound*> soundMap;							  // 028
		BSTHashMap<std::uint32_t, BSSoundInfo*> soundStateMap;						  // 058
		BSTHashMap<std::uint32_t, NiPointer<NiAVObject>> movingRefrMap;				  // 088
		BSTHashMap<const NiAVObject*, const BSISoundOutputModel*> outputOverrideMap;  // 0B8
		BSTHashMap<const BSISoundOutputModel*, REX::Float32> opmFrequencyOverrideMap; // 0E8
		BSTHashMap<std::uint32_t, BSMultisound*> multisoundMap;						  // 118
		BSTHashMap<const NiAVObject*, NiPoint3> locationOverrideMap;				  // 148
		SyncedPlaybackManager syncManager;											  // 178
		void* cachedSoundList;														  // 190 - TODO: `BSTList<BSGameSound*>`
		std::uint32_t currentCacheSize;												  // 198
		std::uint32_t audioThreadID;												  // 19C
		BSAudioManagerThread* updateThread;											  // 1A0
		std::uint32_t audioThreadSleepTime;											  // 1A8
		std::uint32_t audioHWThread;												  // 1AC
		BSAudioInit initSettings;													  // 1B0
		std::uint32_t audioCacheSize;												  // 200
		std::uint32_t maxAudioCacheSize;											  // 204
		std::uint32_t maxSizeForCachedSound;										  // 208
		std::uint32_t stateFlags;													  // 20C
		REX::Float32 masterVolume;													  // 210
		std::uint8_t asyncPriorityThreshold;										  // 214
		REX::Float32 invSpeedInUnitsPerMS;											  // 218
		BSAudioCallbacks audioCallbacks;											  // 220
	};
	static_assert(sizeof(BSAudioManager) == 0x238);
}
