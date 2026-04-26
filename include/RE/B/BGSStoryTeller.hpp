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

	class __declspec(novtable) BGSStoryTeller
		: public BSTEventSink<TESQuestStageItemDoneEvent>, // 00
		  public BSTSingletonSDM<BGSStoryTeller>		   // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryTeller };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryTeller };

		~BGSStoryTeller() override; // 00

		// override (BSTEventSink<TESQuestStageItemDoneEvent>)
		BSEventNotifyControl ProcessEvent(const TESQuestStageItemDoneEvent& a_event, BSTEventSource<TESQuestStageItemDoneEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BGSStoryTeller* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSStoryTeller**>{ ID::BGSStoryTeller::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] static BSSpinLock& GetQuestsLock()
		{
			static const auto QUESTS_LOCK = REL::Relocation<BSSpinLock*>{ ID::BGSStoryTeller::QuestsLock };
			return *QUESTS_LOCK;
		}

		[[nodiscard]] static BSSpinLock& GetFindQuestLock()
		{
			static const auto FIND_QUEST_LOCK = REL::Relocation<BSSpinLock*>{ ID::BGSStoryTeller::FindQuestLock };
			return *FIND_QUEST_LOCK;
		}

		// members
		BSTArray<BGSStoryEvent> immediateEvents;
		BSTArray<BGSStoryEvent> storyEventQueue;
		BSTArray<TESQuest*> queuedStartQuests;
		BSTArray<TESQuest*> runningQuests;
		BSTArray<TESQuest*> queuedStopQuests;
		BSTArray<TESQuest*> infoClearQuests;
		BSTArray<TESQuest*> helloTopicQuests;
		BSTArray<TESQuest*> greetingTopicQuests;
		bool startUpQuestsInitted;
		BSTHashMap<std::uint32_t, BSTArray<BSTPair<std::uint32_t, std::uint32_t>>*> questStageWaitMap;
	};
}
