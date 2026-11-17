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
	class __declspec(novtable) PipboyQuestData :
		public PipboyDataGroup,								   // 0x00
		public BSTEventSink<PlayerCharacterQuestEvent::Event>, // 0x89
		public BSTEventSink<TESQuestEvent::Event>			   // 0xA0
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PipboyQuestData;
		inline static constexpr const auto& VTABLE = VTABLE::PipboyQuestData;

		~PipboyQuestData() override; // 0x00

		auto ProcessEvent(
			const PlayerCharacterQuestEvent::Event& a_event,
			BSTEventSource<PlayerCharacterQuestEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01
		auto ProcessEvent(
			const TESQuestEvent::Event& a_event,
			BSTEventSource<TESQuestEvent::Event>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (PipboyDataGroup)
		void Populate(bool a_unk01) override; // 0x03
		void DoClearData() override;		  // 0x04
		void DoClearSink() override;		  // 0x05

		// members
		std::uint32_t sortIndex;				// 0xA8
		PipboyArray* questArray;				// 0xB0
		std::array<void*, 6> objectivesByQuest; // 0xB8 - BSTHashMap<BSTPair<TESQuest*, std::uint64_t>,
												// BSTArray<BGSInstancedQuestObjective>*>
	};

	static_assert(sizeof(PipboyQuestData) == 0xE8);
}
