#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/I/IKeywordFormBase.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	enum class SCENE_ACTOR_FLAG : std::uint32_t;

	class BGSSceneAction;
	class BGSScenePhase;

	class __declspec(novtable) BGSScene
		: public TESForm,		  // 00
		  public IKeywordFormBase // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSScene };
		inline static constexpr auto VTABLE{ VTABLE::BGSScene };
		inline static constexpr auto FORM_TYPE{ FormType::kScene };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kActive = 1ui32 << 31
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kBeginOnQuestStart = 1 << 0,
			kStopQuestOnEnd = 1 << 1,
			kShowAllTextInEditor = 1 << 2,
			kRepeats = 1 << 3,
			kInterruptible = 1 << 4,
			kPlayerDialogue = 1 << 5,
			kNoPlayerExitDialogue = 1 << 6,
			kPlayerRadioStation = 1 << 7,
			kBroadCastScene = 1 << 8,
			kPauseActorsCurrentSceneinDialogue = 1 << 9,
			kLookAhead = 1 << 10,
			kAllowDialogueCamera = 1 << 11,
			kNoFollowerIdleChatter = 1 << 12
		};

		enum class NiFlags : std::uint32_t
		{
			kNone = 0,
			kActive = 1 << 0,
			kPhaseActionDone = 1 << 1,
			kPauseScene = 1 << 2,
			kSceneScriptFinished = 1 << 3,
			kNeedsToEnd = 1 << 4,
			kRandom = 1 << 5,
			kCombatPause = 1 << 6,
			kDialoguePause = 1 << 7,
			kObserveCombatPause = 1 << 8,
			kPlayerWalkedAway = 1 << 9,
			kNoUpdate = 1 << 10,
			kInheritedPhases = 1 << 11,
			kQueueActive = 1 << 20,
			kSceneJumpActive = 1 << 21,
			kGamePause = 1 << 22
		};

		enum class BehaviourFlags : std::uint32_t
		{
			kNone = 0,
			kDeathPause = 1 << 0,
			kDeathEnd = 1 << 1,
			kCombatPause = 1 << 2,
			kCombatEnd = 1 << 3,
			kDialoguePause = 1 << 4,
			kDialogueEnd = 1 << 5,
			kOBS_COMPause = 1 << 6,
			kOBS_COMEnd = 1 << 7
		};

		void ResetAllSceneActions()
		{
			using FuncType = decltype(&BGSScene::ResetAllSceneActions);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSScene::ResetAllSceneActions };
			FUNC(this);
		}

		void SetSceneActive(bool a_set)
		{
			using FuncType = decltype(&BGSScene::SetSceneActive);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSScene::SetSceneActive };
			FUNC(this, a_set);
		}

		// members
		REX::EnumSet<NiFlags, std::uint32_t> niFlags;								 // 28
		BSTArray<BGSScenePhase*> phases;											 // 30
		BSTArray<TESFormID> actors;													 // 48
		BSTArray<REX::EnumSet<SCENE_ACTOR_FLAG, std::uint32_t>> actorFlags;			 // 60
		BSTArray<REX::EnumSet<BehaviourFlags, std::uint32_t>> actorProgressionFlags; // 78
		BSTArray<BGSSceneAction*> actions;											 // 90
		TESQuest* parentQuest;														 // A8
		BGSScene* templateScene;													 // B0
		REX::EnumSet<Flags, std::uint32_t> flags;									 // B8
		TESCondition repeatConditions;												 // C0
		std::uint32_t speakerID;													 // C8
		std::uint32_t currentActivePhase;											 // CC
		std::uint32_t startPhase;													 // D0
		REX::Float32 randomSceneTimer;												 // D4
		REX::Float32 maxREFDistanceCenter;											 // D8
		ObjectRefHandle targetRef;													 // DC
		bool shouldNotRotateToTrack;												 // E0
	};
	static_assert(sizeof(BGSScene) == 0xE8);
}
