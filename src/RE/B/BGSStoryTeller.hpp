#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTTuple.hpp"

namespace RE
{
	class BGSStoryEvent;
	class BSSpinLock;
	class TESQuestStageItemDoneEvent;

	class __declspec(novtable) BGSStoryTeller :
		public BSTEventSink<TESQuestStageItemDoneEvent>, // 0x00
		public BSTSingletonSDM<BGSStoryTeller>			 // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSStoryTeller;
		inline static constexpr const auto& VTABLE = VTABLE::BGSStoryTeller;

		~BGSStoryTeller() override; // 0x00

		// override (BSTEventSink<TESQuestStageItemDoneEvent>)
		auto ProcessEvent(
			const TESQuestStageItemDoneEvent& a_event,
			BSTEventSource<TESQuestStageItemDoneEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSStoryTeller*
		{
			static const auto SINGLETON = REL::Relocation<BGSStoryTeller**>(ID::BGSStoryTeller::Singleton);
			return *SINGLETON;
		}

		[[nodiscard]]
		static auto GetQuestsLock() noexcept -> BSSpinLock&
		{
			static const auto QUESTS_LOCK = REL::Relocation<BSSpinLock*>(ID::BGSStoryTeller::QuestsLock);
			return *QUESTS_LOCK;
		}

		[[nodiscard]]
		static auto GetFindQuestLock() noexcept -> BSSpinLock&
		{
			static const auto FIND_QUEST_LOCK = REL::Relocation<BSSpinLock*>(ID::BGSStoryTeller::FindQuestLock);
			return *FIND_QUEST_LOCK;
		}

		// members
		BSTArray<BGSStoryEvent> immediateEvents;													   // 0x10
		BSTArray<BGSStoryEvent> storyEventQueue;													   // 0x28
		BSTArray<TESQuest*> queuedStartQuests;														   // 0x40
		BSTArray<TESQuest*> runningQuests;															   // 0x58
		BSTArray<TESQuest*> queuedStopQuests;														   // 0x70
		BSTArray<TESQuest*> infoClearQuests;														   // 0x88
		BSTArray<TESQuest*> helloTopicQuests;														   // 0xA0
		BSTArray<TESQuest*> greetingTopicQuests;													   // 0xB8
		bool startUpQuestsInitted;																	   // 0xD0
		BSTHashMap<std::uint32_t, BSTArray<BSTPair<std::uint32_t, std::uint32_t>>*> questStageWaitMap; // 0xD8
	};

	static_assert(sizeof(BGSStoryTeller) == 0x108);
}
