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

	class __declspec(novtable) BGSScene :
		public TESForm,			// 0x00
		public IKeywordFormBase // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSScene;
		inline static constexpr const auto& VTABLE = VTABLE::BGSScene;
		inline static constexpr auto FORM_TYPE = FormType::Scene;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				Active = static_cast<std::uint32_t>(1) << 31
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			BeginOnQuestStart = 1 << 0,
			StopQuestOnEnd = 1 << 1,
			ShowAllTextInEditor = 1 << 2,
			Repeats = 1 << 3,
			Interruptible = 1 << 4,
			PlayerDialogue = 1 << 5,
			NoPlayerExitDialogue = 1 << 6,
			PlayerRadioStation = 1 << 7,
			BroadCastScene = 1 << 8,
			PauseActorsCurrentSceneinDialogue = 1 << 9,
			LookAhead = 1 << 10,
			AllowDialogueCamera = 1 << 11,
			NoFollowerIdleChatter = 1 << 12
		};

		enum class NiFlags : std::uint32_t
		{
			None = 0,
			Active = 1 << 0,
			PhaseActionDone = 1 << 1,
			PauseScene = 1 << 2,
			SceneScriptFinished = 1 << 3,
			NeedsToEnd = 1 << 4,
			Random = 1 << 5,
			CombatPause = 1 << 6,
			DialoguePause = 1 << 7,
			ObserveCombatPause = 1 << 8,
			PlayerWalkedAway = 1 << 9,
			NoUpdate = 1 << 10,
			InheritedPhases = 1 << 11,
			QueueActive = 1 << 20,
			SceneJumpActive = 1 << 21,
			GamePause = 1 << 22
		};

		enum class BehaviourFlags : std::uint32_t
		{
			None = 0,
			DeathPause = 1 << 0,
			DeathEnd = 1 << 1,
			CombatPause = 1 << 2,
			CombatEnd = 1 << 3,
			DialoguePause = 1 << 4,
			DialogueEnd = 1 << 5,
			OBS_COMPause = 1 << 6,
			OBS_COMEnd = 1 << 7
		};

		~BGSScene() override; // 0x00

		void ResetAllSceneActions()
		{
			using FuncType = decltype(&BGSScene::ResetAllSceneActions);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSScene::ResetAllSceneActions);
			std::invoke(FUNC, this);
		}

		void SetSceneActive(bool a_set)
		{
			using FuncType = decltype(&BGSScene::SetSceneActive);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSScene::SetSceneActive);
			std::invoke(FUNC, this, a_set);
		}

		// members
		REX::EnumSet<NiFlags, std::uint32_t> niFlags;								 // 0x28
		BSTArray<BGSScenePhase*> phases;											 // 0x30
		BSTArray<TESFormID> actors;													 // 0x48
		BSTArray<REX::EnumSet<SCENE_ACTOR_FLAG, std::uint32_t>> actorFlags;			 // 0x60
		BSTArray<REX::EnumSet<BehaviourFlags, std::uint32_t>> actorProgressionFlags; // 0x78
		BSTArray<BGSSceneAction*> actions;											 // 0x90
		TESQuest* parentQuest;														 // 0xA8
		BGSScene* templateScene;													 // 0xB0
		REX::EnumSet<Flags, std::uint32_t> flags;									 // 0xB8
		TESCondition repeatConditions;												 // 0xC0
		std::uint32_t speakerID;													 // 0xC8
		std::uint32_t currentActivePhase;											 // 0xCC
		std::uint32_t startPhase;													 // 0xD0
		REX::Float32 randomSceneTimer;												 // 0xD4
		REX::Float32 maxREFDistanceCenter;											 // 0xD8
		ObjectRefHandle targetRef;													 // 0xDC
		bool shouldNotRotateToTrack;												 // 0xE0
	};

	static_assert(sizeof(BGSScene) == 0xE8);
}
