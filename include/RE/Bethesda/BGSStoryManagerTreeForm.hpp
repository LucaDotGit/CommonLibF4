#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSString.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSmallIndexScatterTable.hpp"
#include "RE/Bethesda/FormComponents.hpp"
#include "RE/Bethesda/TESCondition.hpp"
#include "RE/Bethesda/TESForms.hpp"
#include "RE/NetImmerse/NiSmartPointer.hpp"

namespace RE
{
	class BGSBaseAlias;
	class BGSQuestObjective;
	class BGSRegisteredStoryEvent;
	class BGSStoryEvent;
	class BGSStoryManagerTreeForm;
	class PeriodicUpdateTimer;
	class BGSStoryManagerQuestNode;
	class QueuedPromoteQuestTask;
	class TESFile;
	class TESQuestStage;

	class __declspec(novtable) BGSStoryManagerTreeVisitor
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeVisitor };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeVisitor };

		enum class VisitControl;

		virtual ~BGSStoryManagerTreeVisitor(); // 00

		virtual VisitControl VisitBranchNode(BGSStoryManagerBranchNode& a_node) = 0;				// 01
		virtual VisitControl VisitQuestNode(BGSStoryManagerQuestNode& a_node, bool a_canReset) = 0; // 02
		virtual VisitControl VisitQuest(TESQuest& a_quest) = 0;										// 03
		virtual void Revert() = 0;																	// 04

		// members
		PeriodicUpdateTimer* timer;						   // 08
		std::int32_t currentCursorDepth;				   // 10
		BGSStoryManagerQuestNode* lastQuestParent;		   // 18
		BSTArray<BGSStoryManagerTreeForm*> cursorAncestry; // 20
		std::uint32_t queryID;							   // 38
	};
	static_assert(sizeof(BGSStoryManagerTreeVisitor) == 0x40);

	class __declspec(novtable) BGSStoryManagerTreeForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerTreeForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerTreeForm };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kNONE };

		// add
		virtual std::uint32_t QChildCount() const { return 0; }														// 4A
		virtual BGSStoryManagerTreeForm* GetChild([[maybe_unused]] std::uint32_t a_index) const { return nullptr; } // 4B
		virtual TESCondition* QConditions() = 0;																	// 4C
		virtual BGSStoryManagerTreeVisitor::VisitControl AcceptVisitor(BGSStoryManagerTreeVisitor& a_visitor) = 0;	// 4D

		// members
		std::uint32_t lastVisitorID; // 20
	};
	static_assert(sizeof(BGSStoryManagerTreeForm) == 0x28);

	struct QUEST_DATA
	{
	public:
		enum class Flags
		{
			kStopStart = static_cast<std::underlying_type_t<Flags>>(-1),
			kNone = 0,
			kEnabled = 1 << 0,
			kCompleted = 1 << 1,
			kAddIdleToHello = 1 << 2,
			kAllowRepeatStages = 1 << 3,
			kStartsEnabled = 1 << 4,
			kDisplayedInHUD = 1 << 5,
			kFailed = 1 << 6,
			kStageWait = 1 << 7,
			kRunOnce = 1 << 8,
			kExcludeFromExport = 1 << 9,
			kWarnOnAliasFillFailure = 1 << 10,
			kActive = 1 << 11,
			kRepeatsConditions = 1 << 12,
			kKeepInstance = 1 << 13,
			kWantDormant = 1 << 14,
			kHasDialogueData = 1 << 15
		};

		enum class Type
		{
			kNone,
			kMainQuest,
			kBrotherhoodOfSteel,
			kInstitute,
			kMinutemen,
			kRailroad,
			kMiscellaneous,
			kSideQuest,
			kDLC01,
			kDLC02,
			kDLC03,
			kDLC04,
			kDLC05,
			kDLC06,
			kDLC07
		};

		// members
		float questDelayTime;					 // 00
		REX::EnumSet<Flags, std::int16_t> flags; // 04
		std::int8_t priority;					 // 06
		REX::Enum<Type, std::uint8_t> questType; // 07
	};
	static_assert(sizeof(QUEST_DATA) == 0x8);

	class BGSQuestInstanceText
	{
	public:
		struct StringData
		{
		public:
			// members
			std::uint32_t aliasID;	  // 00
			TESFormID fullNameFormID; // 04
		};
		static_assert(sizeof(StringData) == 0x8);

		struct GlobabValueData
		{
		public:
			// members
			const TESGlobal* global; // 00
			float value;			 // 08
		};
		static_assert(sizeof(GlobabValueData) == 0x10);

		static void ParseString(BSString* a_inOutText, const TESQuest* a_quest, std::uint32_t a_instanceID)
		{
			using func_t = decltype(&BGSQuestInstanceText::ParseString);
			static REL::Relocation<func_t> func{ REL::RelocationID(141681, 2206630) };
			return func(a_inOutText, a_quest, a_instanceID);
		}

		// Members
		std::uint32_t id;										   // 00
		BSTArray<BGSQuestInstanceText::StringData> stringData;	   // 08
		BSTArray<BGSQuestInstanceText::GlobabValueData> valueData; // 20
		std::uint16_t journalStage;								   // 38
		std::uint16_t journalStageItem;							   // 3A
	};
	static_assert(sizeof(BGSQuestInstanceText) == 0x40);

	class __declspec(novtable) TESQuest
		: public BGSStoryManagerTreeForm, // 000
		  public TESFullName			  // 028
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESQuest };
		inline static constexpr auto VTABLE{ VTABLE::TESQuest };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kQUST };

		struct AliasesAccess;
		struct ListObjectivesAccess;
		struct ListStagesAccess;

		struct RecordFlags
		{
			enum RecordFlag : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kPartialForm = 1 << 14
			};
		};

		bool SetStage(std::uint16_t a_stage)
		{
			using func_t = decltype(&TESQuest::SetStage);
			static REL::Relocation<func_t> func{ REL::RelocationID(952799, 2207743) };
			return func(this, a_stage);
		}

		BSPointerHandle<TESObjectREFR>* GetAliasedRef(BSPointerHandle<TESObjectREFR>* a_result, std::uint32_t a_aiAliasID)
		{
			using func_t = decltype(&TESQuest::GetAliasedRef);
			static REL::Relocation<func_t> func{ REL::RelocationID(847223, 2207810) };
			return func(this, a_result, a_aiAliasID);
		}

		// members
		BSTArray<BGSQuestInstanceText*> instanceData;												  // 038
		std::uint32_t currentInstanceID;															  // 050
		BSTArray<BSTTuple<TESFile*, std::uint32_t>> fileOffsets;									  // 058
		BSTArray<BGSBaseAlias*> aliases;															  // 070
		BSTHashMap<std::uint32_t, BGSLocation*> aliasedLocMap;										  // 088
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
		BSTHashMap<BGSDialogueBranch*, BSTArray<TESTopic*>*> branchedDialogues[2];					  // 1A0
		BSTArray<TESTopic*> topics[6];																  // 200
		BSTArray<BGSScene*> scenes;																	  // 290
		BSTArray<TESGlobal*>* textGlobal;															  // 2A8
		std::uint32_t totalRefsAliased;																  // 2B0
		std::uint16_t currentStage;																	  // 2B4
		bool alreadyRun;																			  // 2B6
		BSString formEditorID;																		  // 2B8
		const BGSStoryEvent* startEventData;														  // 2C8
		NiPointer<QueuedPromoteQuestTask> promoteTask;												  // 2D0
		BSTArray<ObjectRefHandle> promotedRefsArray;												  // 2D8
	};
	static_assert(sizeof(TESQuest) == 0x2F0);

	class __declspec(novtable) BGSStoryManagerNodeBase
		: public BGSStoryManagerTreeForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerNodeBase };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerNodeBase };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kNONE };

		// add
		virtual std::uint32_t GetQuestsStarted() const = 0; // 4E

		// members
		BGSStoryManagerBranchNode* parent;	  // 28
		BGSStoryManagerNodeBase* prevSibling; // 30
		std::uint32_t maxQuests;			  // 38
		std::uint32_t flags;				  // 3C
		TESCondition conditions;			  // 40
	};
	static_assert(sizeof(BGSStoryManagerNodeBase) == 0x48);

	class __declspec(novtable) BGSStoryManagerBranchNode
		: public BGSStoryManagerNodeBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerBranchNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerBranchNode };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSMBN };

		// members
		BSTArray<BGSStoryManagerNodeBase*> children; // 48
	};
	static_assert(sizeof(BGSStoryManagerBranchNode) == 0x60);

	class __declspec(novtable) BGSStoryManagerQuestNode
		: public BGSStoryManagerNodeBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerQuestNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerQuestNode };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSMQN };

		// members
		BSTArray<TESQuest*> children;						  // 48
		BSTHashMap<TESQuest*, std::uint32_t> perQuestFlags;	  // 60
		BSTHashMap<TESQuest*, float> perQuestHoursUntilReset; // 90
		std::uint32_t numQuestsToStart;						  // C0
		BSTArray<float> childrenLastRun;					  // C8
	};
	static_assert(sizeof(BGSStoryManagerQuestNode) == 0xE0);

	class __declspec(novtable) BGSStoryManagerEventNode
		: public BGSStoryManagerBranchNode // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSStoryManagerEventNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSStoryManagerEventNode };
		inline static constexpr auto FORMTYPE{ ENUM_FORMTYPE::kSMEN };

		// members
		const BGSRegisteredStoryEvent* event; // 60
	};
	static_assert(sizeof(BGSStoryManagerEventNode) == 0x68);
}
