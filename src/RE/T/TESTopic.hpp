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

	class __declspec(novtable) TESTopic :
		public TESForm,	   // 0x00
		public TESFullName // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESTopic;
		inline static constexpr const auto& VTABLE = VTABLE::TESTopic;
		inline static constexpr auto FORM_TYPE = FormType::Topic;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				PartialForm = 1 << 14
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
				std::uint16_t left;	 // 0x00
				std::uint16_t right; // 0x02
			};

			static_assert(sizeof(Node) == 0x04);

			// members
			Node roots; // 0x00
		};

		static_assert(sizeof(InfoTree) == 0x04);

		auto InitDialogueItem(
			DialogueItem& a_outItem,
			TESObjectREFR* a_speaker,
			TESObjectREFR* a_target,
			TESTopicInfo* a_info,
			TESTopic* a_previousTopic,
			BSSimpleList<DialogueItem*>* a_conversationList = nullptr) -> bool
		{
			using FuncType = decltype(&TESTopic::InitDialogueItem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopic::InitDialogueItem);
			return std::invoke(FUNC, this, a_outItem, a_speaker, a_target, a_info, a_previousTopic, a_conversationList);
		}

		// members
		DIALOGUE_DATA data;					   // 0x30
		std::uint32_t priorityAndJournalIndex; // 0x34
		BGSDialogueBranch* ownerBranch;		   // 0x38
		TESQuest* ownerQuest;				   // 0x40
		BGSKeyword* subtypeKeyword;			   // 0x48
		SimpleArray<TESTopicInfo*> topicInfos; // 0x50
		InfoTree* infoTree;					   // 0x58
		std::uint32_t numTopicInfos;		   // 0x60
		std::uint32_t topicInfoAllocSize;	   // 0x64
		std::uint32_t firstFileOffset;		   // 0x68
		BSFixedString formEditorID;			   // 0x70
	};

	static_assert(sizeof(TESTopic) == 0x78);
}
