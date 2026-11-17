#pragma once

#include "RE/T/TESCondition.hpp"

namespace RE
{
	enum class SCENE_ACTION_TYPE : std::int32_t;

	class __declspec(novtable) BGSSceneAction
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSceneAction;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSceneAction;

		enum class Flags : std::uint32_t
		{
			PlayerUseDialogueSubtypePositive = 1 << 7,
			PlayerUseDialogueSubtypeNegative = 1 << 8,
			PlayerUseDialogueSubtypeNeutral = 1 << 9,
			UseDialogueSubtype = 1 << 10,
			PlayerUseDialogueSubtypeQuestion = 1 << 11,
			FaceTarget = 1 << 15,
			HeadTrackPlayer = 1 << 17,
			IgnoreForCompletion = 1 << 19,
			CameraSpeakerTarget = 1 << 21
		};

		enum class Status : std::int8_t
		{
			Stopped = 0,
			Running = 1,
			Complete = 2
		};

		class STARTSCENEACTIONDATA
		{
		public:
			BGSScene* pScene{nullptr};
			std::uint16_t sceneStartPhase{0};
			TESQuest* parentQuest{nullptr};
			TESCondition sceneConditions;
		};

		virtual ~BGSSceneAction(); // 0x00

		// add
		virtual void Load();																	  // 0x01
		virtual void InitItem();																  // 0x02
		virtual void OnDelete();																  // 0x03
		virtual void ClearData();																  // 0x04
		virtual void Copy();																	  // 0x05
		virtual auto QIsLooping() -> bool;														  // 0x06
		virtual auto QFaceHeadTrackTarget(const BGSScene* scene) -> bool;						  // 0x07
		virtual auto GetActionType() const -> SCENE_ACTION_TYPE = 0;							  // 0x08
		virtual auto QActionCanEnd() -> bool;													  // 0x09
		virtual auto IsPackageActive(BGSScene* scene, TESPackage* package, Actor* actor) -> bool; // 0x0A
		virtual void LoadGame();																  // 0x0B
		virtual void SaveGame();																  // 0x0C
		virtual void Revert();																	  // 0x0D
		virtual void InitLoadGame();															  // 0x0E
		virtual void ResetActionData();															  // 0x0F
		virtual void SetInput();																  // 0x10
		virtual auto GetActionPercentDone(const BGSScene* scene) -> REX::Float32;				  // 0x11
		virtual void StartAction(BGSScene* scene);												  // 0x12
		virtual void EndAction(BGSScene* scene);												  // 0x13
		virtual void CleanUpActionActor(BGSScene* scene);										  // 0x14
		virtual void UpdateAction(BGSScene* scene);												  // 0x14

		// members
		TESFormID actorID;						  // 0x08
		std::uint16_t startPhase;				  // 0x0C
		std::uint16_t endPhase;					  // 0x0E
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x10
		REX::Enum<Status, std::int8_t> status;	  // 0x14
		std::uint32_t uniqueID;					  // 0x18
	};

	static_assert(sizeof(BGSSceneAction) == 0x20);
}
