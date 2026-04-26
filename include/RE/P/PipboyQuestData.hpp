#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/P/PipboyDataGroup.hpp"

namespace RE::PlayerCharacterQuestEvent
{
	class Event;
}

namespace RE::TESQuestEvent
{
	class Event;
}

namespace RE
{
	class __declspec(novtable) PipboyQuestData
		: public PipboyDataGroup,								 // 00
		  public BSTEventSink<PlayerCharacterQuestEvent::Event>, // 89
		  public BSTEventSink<TESQuestEvent::Event>				 // A0
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyQuestData };
		inline static constexpr auto VTABLE{ VTABLE::PipboyQuestData };

		~PipboyQuestData() override; // 00

		BSEventNotifyControl ProcessEvent(const PlayerCharacterQuestEvent::Event& a_event, BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) override; // 01
		BSEventNotifyControl ProcessEvent(const TESQuestEvent::Event& a_event, BSTEventSource<TESQuestEvent::Event>* a_eventSource) override;						  // 01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 03
		void DoClearData() override;		  // 04
		void DoClearSink() override;		  // 05

		// members
		std::uint32_t sortIndex;				// A8
		PipboyArray* questArray;				// B0
		std::array<void*, 6> objectivesByQuest; // B8 - BSTHashMap<BSTPair<TESQuest*, std::uint64_t>, BSTArray<BGSInstancedQuestObjective>*>
	};
	static_assert(sizeof(PipboyQuestData) == 0xE8);
}
