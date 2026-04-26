#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/D/DIALOGUE_DATA.hpp"
#include "RE/S/SimpleArray.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class DialogueItem;

	class __declspec(novtable) TESTopic
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESTopic };
		inline static constexpr auto VTABLE{ VTABLE::TESTopic };
		inline static constexpr auto FORM_TYPE{ FormType::kTopic };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kPartialForm = 1 << 14
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class InfoTree
		{
		public:
			class Node
			{
			public:
				// members
				std::uint16_t left;	 // 00
				std::uint16_t right; // 02
			};
			static_assert(sizeof(Node) == 0x04);

			// members
			Node roots; // 00
		};
		static_assert(sizeof(InfoTree) == 0x04);

		bool InitDialogueItem(DialogueItem& a_outItem, TESObjectREFR* a_speaker, TESObjectREFR* a_target, TESTopicInfo* a_info, TESTopic* a_previousTopic, BSSimpleList<DialogueItem*>* a_conversationList = nullptr)
		{
			using FuncType = decltype(&TESTopic::InitDialogueItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopic::InitDialogueItem };
			return std::invoke(FUNC, this, a_outItem, a_speaker, a_target, a_info, a_previousTopic, a_conversationList);
		}

		// members
		DIALOGUE_DATA data;					   // 30
		std::uint32_t priorityAndJournalIndex; // 34
		BGSDialogueBranch* ownerBranch;		   // 38
		TESQuest* ownerQuest;				   // 40
		BGSKeyword* subtypeKeyword;			   // 48
		SimpleArray<TESTopicInfo*> topicInfos; // 50
		InfoTree* infoTree;					   // 58
		std::uint32_t numTopicInfos;		   // 60
		std::uint32_t topicInfoAllocSize;	   // 64
		std::uint32_t firstFileOffset;		   // 68
		BSFixedString formEditorID;			   // 70
	};
	static_assert(sizeof(TESTopic) == 0x78);
}
