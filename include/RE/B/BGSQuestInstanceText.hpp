#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class BGSQuestInstanceText
	{
	public:
		class StringData
		{
		public:
			// members
			std::uint32_t aliasID;	  // 00
			TESFormID fullNameFormID; // 04
		};
		static_assert(sizeof(StringData) == 0x08);

		class GlobalValueData
		{
		public:
			// members
			TESGlobal* global;	// 00
			REX::Float32 value; // 08
		};
		static_assert(sizeof(GlobalValueData) == 0x10);

		GAME_HEAP_REDEFINE_NEW(BGSQuestInstanceText);

		static void ParseString(BSString* a_inOutText, const TESQuest* a_quest, std::uint32_t a_instanceID)
		{
			using FuncType = decltype(&BGSQuestInstanceText::ParseString);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSQuestInstanceText::ParseString };
			std::invoke(FUNC, a_inOutText, a_quest, a_instanceID);
		}

		// members
		std::uint32_t id;						  // 00
		BSTArray<StringData> stringDataArray;	  // 08
		BSTArray<GlobalValueData> valueDataArray; // 20
		std::uint16_t journalStage;				  // 38
		std::uint16_t journalStageItem;			  // 3A
	};
	static_assert(sizeof(BGSQuestInstanceText) == 0x40);
}
