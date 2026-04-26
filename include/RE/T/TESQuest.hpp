#pragma once

#include "RE/B/BGSStoryManagerTreeForm.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSmallIndexScatterTable.hpp"
#include "RE/B/BSTTuple.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/Q/QUEST_DATA.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class BGSQuestInstanceText;
	class BGSQuestObjective;
	class BGSStoryEvent;
	class QueuedPromoteQuestTask;
	class TESQuestStage;

	class __declspec(novtable) TESQuest
		: public BGSStoryManagerTreeForm, // 000
		  public TESFullName			  // 028
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESQuest };
		inline static constexpr auto VTABLE{ VTABLE::TESQuest };
		inline static constexpr auto FORM_TYPE{ FormType::kQuest };

		class AliasesAccess
		{
		public:
		};
		static_assert(std::is_empty_v<AliasesAccess>);

		class ListObjectivesAccess
		{
		public:
		};
		static_assert(std::is_empty_v<ListObjectivesAccess>);

		class ListStagesAccess
		{
		public:
		};
		static_assert(std::is_empty_v<ListStagesAccess>);

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kFlags = 1 << 1,
				kScriptDelay = 1 << 2,
				kAlreadyRun = 1 << 26,
				kInstances = 1 << 27,
				kRunData = 1 << 28,
				kObjectives = 1 << 29,
				kScript = 1 << 30,
				kStages = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

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

		[[nodiscard]] BGSBaseAlias* GetAliasByID(std::uint32_t a_id) const;
		[[nodiscard]] BGSBaseAlias* GetAliasByName(const BSFixedString& a_name) const;
		[[nodiscard]] ObjectRefHandle GetAliasedRef(ObjectRefHandle* a_result, std::uint32_t a_aiAliasID);
		bool SetStage(std::uint16_t a_stage);

		// members
		BSTArray<BGSQuestInstanceText*> instanceDataArray;											  // 038
		std::uint32_t currentInstanceID;															  // 050
		BSTArray<BSTPair<TESFile*, std::uint32_t>> fileOffsets;										  // 058
		BSTArray<BGSBaseAlias*> aliases;															  // 070
		BSTHashMap<TESFormID, BGSLocation*> aliasedLocMap;											  // 088
		BSTArray<BSTSmallArray<ObjectRefHandle>> aliasedHandles;									  // 0B8
		mutable BSReadWriteLock aliasAccessLock;													  // 0D0
		BGSLocation* nonDormantLocation;															  // 0D8
		TESGlobal* questCompleteXPGlobal;															  // 0E0
		BSFixedString swfFile;																		  // 0E8
		QUEST_DATA data;																			  // 0F0
		std::uint32_t eventID;																		  // 0F8
		BSTArray<TESQuestStage*> stages;															  // 100
		BSTArray<BGSQuestObjective*> objectives;													  // 118
		BSTSmallIndexScatterTable<BSTArray<TESQuestStage*>, ListStagesAccess> stageTable;			  // 130
		BSTSmallIndexScatterTable<BSTArray<BGSQuestObjective*>, ListObjectivesAccess> objectiveTable; // 150
		BSTSmallIndexScatterTable<BSTArray<BGSBaseAlias*>, AliasesAccess> aliasesTable;				  // 170
		TESCondition objConditions;																	  // 190
		TESCondition storyManagerConditions;														  // 198
		std::array<BSTHashMap<BGSDialogueBranch*, BSTArray<TESTopic*>*>, 2> branchedDialogues;		  // 1A0
		std::array<BSTArray<TESTopic*>, 6> topics;													  // 200
		BSTArray<BGSScene*> scenes;																	  // 290
		BSTArray<TESGlobal*>* textGlobal;															  // 2A8
		std::uint32_t totalRefsAliased;																  // 2B0
		std::uint16_t currentStage;																	  // 2B4
		bool alreadyRun;																			  // 2B6
		BSString formEditorID;																		  // 2B8
		BGSStoryEvent* startEventData;																  // 2C8
		NiPointer<QueuedPromoteQuestTask> promoteTask;												  // 2D0
		BSTArray<ObjectRefHandle> promotedRefsArray;												  // 2D8
	};
	static_assert(sizeof(TESQuest) == 0x2F0);
}
