#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/H/HUDSubtitleDisplayEvent.hpp"
#include "RE/S/SubtitleInfo.hpp"

namespace RE
{
	class SubtitleManager
		: public BSTSingletonSDM<SubtitleManager> // 00
	{
	public:
		[[nodiscard]] static SubtitleManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<SubtitleManager**>{ ID::SubtitleManager::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] static BSReadWriteLock& GetRWLock()
		{
			static const auto RW_LOCK = REL::Relocation<BSReadWriteLock*>{ ID::SubtitleManager::RWLock };
			return *RW_LOCK;
		}

		// members
		BSTArray<SubtitleInfo> subtitlePriorityArray;					  // 08
		ObjectRefHandle currentSpeaker;									  // 20
		BSTValueEventSource<HUDSubtitleDisplayEvent> subtitleDisplayData; // 28
	};
	static_assert(sizeof(SubtitleManager) == 0x50);
}
