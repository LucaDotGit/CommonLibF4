#pragma once

#include "RE/B/BSAudioCallbacks.hpp"
#include "RE/B/BSAudioInit.hpp"
#include "RE/B/BSISoundDescriptor.hpp"
#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSAudio;
	class BSAudioManagerThread;
	class BSGameSound;
	class BSISoundOutputModel;
	class BSMultisound;
	class BSSoundHandle;
	class BSSoundInfo;
	class NiAVObject;
	class SoundMessageList;
	class SoundMessageStack;

	class BSAudioManager
	{
	public:
		enum class StateFlags : std::uint32_t
		{
			None = 0,
			ManagerInitialized = 1 << 0,
			PlatformInitialized = 1 << 1,
			PlatformInitFailed = 1 << 2,
			CacheEnabled = 1 << 3,
			ShuttingDown = 1 << 4,
			RunDisabled = 1 << 5
		};

		class SyncedPlaybackManager
		{
		public:
			// members
			BSTArray<BSTSmallArray<std::uint32_t, 2>*> syncFamilies; // 0x00
		};

		static_assert(sizeof(SyncedPlaybackManager) == 0x18);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BSAudioManager*
		{
			static const auto SINGLETON = REL::Relocation<BSAudioManager**>(ID::BSAudioManager::Singleton);
			return *SINGLETON;
		}

		[[nodiscard]]
		static auto GetPlatformInstance() noexcept -> BSAudio*
		{
			static const auto PLATFORM_INSTANCE = REL::Relocation<BSAudio**>(ID::BSAudioManager::PlatformInstance);
			return *PLATFORM_INSTANCE;
		}

		void ClearCache()
		{
			using FuncType = decltype(&BSAudioManager::ClearCache);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::ClearCache);
			std::invoke(FUNC, this);
		}

		void ClearMaps()
		{
			using FuncType = decltype(&BSAudioManager::ClearMaps);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::ClearMaps);
			std::invoke(FUNC, this);
		}

		auto GetSoundHandle(
			BSSoundHandle& a_outSoundHandle,
			const BSISoundDescriptor* a_descriptor,
			REX::Float32 a_distance,
			std::uint32_t a_usageFlags,
			BSISoundDescriptor::ExtraResolutionData* a_extraData = nullptr) -> bool
		{
			using FuncType = decltype(&BSAudioManager::GetSoundHandle);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::GetSoundHandle);
			return std::invoke(FUNC, this, a_outSoundHandle, a_descriptor, a_distance, a_usageFlags, a_extraData);
		}

		void GetSoundHandleByFile(
			BSSoundHandle& a_outSoundHandle,
			const BSResource::ID& a_fileID,
			std::uint32_t a_usageFlags,
			std::uint8_t a_priority)
		{
			using FuncType = decltype(&BSAudioManager::GetSoundHandleByFile);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::GetSoundHandleByFile);
			std::invoke(FUNC, this, a_outSoundHandle, a_fileID, a_usageFlags, a_priority);
		}

		void GetSoundHandleByName(
			BSSoundHandle& a_outSoundHandle,
			const char* a_soundName,
			REX::Float32 a_distance,
			std::uint32_t a_usageFlags,
			BSISoundDescriptor::ExtraResolutionData* a_extraData)
		{
			using FuncType = decltype(&BSAudioManager::GetSoundHandleByName);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::GetSoundHandleByName);
			std::invoke(FUNC, this, a_outSoundHandle, a_soundName, a_distance, a_usageFlags, a_extraData);
		}

		void Init(RE::BSAudioInit& a_initInfo)
		{
			using FuncType = decltype(&BSAudioManager::Init);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::Init);
			std::invoke(FUNC, this, a_initInfo);
		}

		void KillAll(bool a_waitForCompletion = false, std::chrono::milliseconds a_waitTime = 1'000ms)
		{
			using FuncType = decltype(&BSAudioManager::KillAll);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::KillAll);
			std::invoke(FUNC, this, a_waitForCompletion, a_waitTime);
		}

		void Play(TESFormID a_soundFormID) const
		{
			using FuncType = decltype(&BSAudioManager::Play);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::Play);
			std::invoke(FUNC, this, a_soundFormID);
		}

		void PlayAfter(TESFormID a_soundFormID, std::chrono::milliseconds a_waitTime) const
		{
			using FuncType = decltype(&BSAudioManager::PlayAfter);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::PlayAfter);
			std::invoke(FUNC, this, a_soundFormID, a_waitTime);
		}

		void ResumeAudioThread()
		{
			using FuncType = decltype(&BSAudioManager::ResumeAudioThread);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::ResumeAudioThread);
			std::invoke(FUNC, this);
		}

		void Shutdown()
		{
			using FuncType = decltype(&BSAudioManager::Shutdown);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::Shutdown);
			std::invoke(FUNC, this);
		}

		void SuspendAudioThread()
		{
			using FuncType = decltype(&BSAudioManager::SuspendAudioThread);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BSAudioManager::SuspendAudioThread);
			std::invoke(FUNC, this);
		}

		// members
		std::int32_t messageListIndex;												  // 0x000
		std::int32_t messageProcessingListIndex;									  // 0x004
		std::array<SoundMessageList*, 2> messages;									  // 0x008
		SoundMessageStack* freeMessages;											  // 0x018
		SoundMessageStack* garbageMessages;											  // 0x020
		BSTHashMap<std::uint32_t, BSGameSound*> soundMap;							  // 0x028
		BSTHashMap<std::uint32_t, BSSoundInfo*> soundStateMap;						  // 0x058
		BSTHashMap<std::uint32_t, NiPointer<NiAVObject>> movingRefrMap;				  // 0x088
		BSTHashMap<const NiAVObject*, const BSISoundOutputModel*> outputOverrideMap;  // 0x0B8
		BSTHashMap<const BSISoundOutputModel*, REX::Float32> opmFrequencyOverrideMap; // 0x0E8
		BSTHashMap<std::uint32_t, BSMultisound*> multisoundMap;						  // 0x118
		BSTHashMap<const NiAVObject*, NiPoint3> locationOverrideMap;				  // 0x148
		SyncedPlaybackManager syncManager;											  // 0x178
		void* cachedSoundList;								// 0x190 - To-Do: `BSTList<BSGameSound*>`
		std::uint32_t currentCacheSize;						// 0x198
		REX::W32::THREAD_ID audioThreadID;					// 0x19C
		BSAudioManagerThread* updateThread;					// 0x1A0
		std::uint32_t audioThreadSleepTime;					// 0x1A8
		std::uint32_t audioHWThread;						// 0x1AC
		BSAudioInit initSettings;							// 0x1B0
		std::uint32_t audioCacheSize;						// 0x200
		std::uint32_t maxAudioCacheSize;					// 0x204
		std::uint32_t maxSizeForCachedSound;				// 0x208
		REX::EnumSet<StateFlags, std::uint32_t> stateFlags; // 0x20C
		REX::Float32 masterVolume;							// 0x210
		std::uint8_t asyncPriorityThreshold;				// 0x214
		REX::Float32 invSpeedInUnitsPerMS;					// 0x218
		BSAudioCallbacks audioCallbacks;					// 0x220
	};

	static_assert(sizeof(BSAudioManager) == 0x238);
}
