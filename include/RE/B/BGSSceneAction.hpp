#pragma once

#include "RE/T/TESCondition.hpp"

namespace RE
{
	enum class SCENE_ACTION_TYPE : std::int32_t;

	class __declspec(novtable) BGSSceneAction
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSceneAction };
		inline static constexpr auto VTABLE{ VTABLE::BGSSceneAction };

		enum class Flags : std::uint32_t
		{
			kPlayerUseDialogueSubtypePositive = 1 << 7,
			kPlayerUseDialogueSubtypeNegative = 1 << 8,
			kPlayerUseDialogueSubtypeNeutral = 1 << 9,
			kUseDialogueSubtype = 1 << 10,
			kPlayerUseDialogueSubtypeQuestion = 1 << 11,
			kFaceTarget = 1 << 15,
			kHeadTrackPlayer = 1 << 17,
			kIgnoreForCompletion = 1 << 19,
			kCameraSpeakerTarget = 1 << 21
		};

		enum class Status : std::int8_t
		{
			kStopped = 0,
			kRunning = 1,
			kComplete = 2
		};

		class STARTSCENEACTIONDATA
		{
		public:
			BGSScene* pScene{ nullptr };
			std::uint16_t sceneStartPhase{ 0 };
			TESQuest* parentQuest{ nullptr };
			TESCondition sceneConditions;
		};

		virtual ~BGSSceneAction(); // 00

		// add
		virtual void Load();															  // 01
		virtual void InitItem();														  // 02
		virtual void OnDelete();														  // 03
		virtual void ClearData();														  // 04
		virtual void Copy();															  // 05
		virtual bool QIsLooping();														  // 06
		virtual bool QFaceHeadTrackTarget(const BGSScene* scene);						  // 07
		virtual SCENE_ACTION_TYPE GetActionType() const = 0;							  // 08
		virtual bool QActionCanEnd();													  // 09
		virtual bool IsPackageActive(BGSScene* scene, TESPackage* package, Actor* actor); // 0A
		virtual void LoadGame();														  // 0B
		virtual void SaveGame();														  // 0C
		virtual void Revert();															  // 0D
		virtual void InitLoadGame();													  // 0E
		virtual void ResetActionData();													  // 0F
		virtual void SetInput();														  // 10
		virtual REX::Float32 GetActionPercentDone(const BGSScene* scene);				  // 11
		virtual void StartAction(BGSScene* scene);										  // 12
		virtual void EndAction(BGSScene* scene);										  // 13
		virtual void CleanUpActionActor(BGSScene* scene);								  // 14
		virtual void UpdateAction(BGSScene* scene);										  // 14

		// members
		TESFormID actorID;						  // 08
		std::uint16_t startPhase;				  // 0C
		std::uint16_t endPhase;					  // 0E
		REX::EnumSet<Flags, std::uint32_t> flags; // 10
		REX::Enum<Status, std::int8_t> status;	  // 14
		std::uint32_t uniqueID;					  // 18
	};
	static_assert(sizeof(BGSSceneAction) == 0x20);
}
