#pragma once

#include "RE/A/AITimer.hpp"
#include "RE/A/ActorPackage.hpp"
#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/D/DEFAULT_OBJECT.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t;
	enum class DIALOGUE_SUBTYPE : std::int32_t;
	enum class DIALOGUE_TYPE : std::int32_t;
	enum class WEAPON_CULL_TYPE : std::int32_t;

	class CachedValues;
	class HighProcessData;
	class MiddleHighProcessData;
	class MiddleLowProcessData;
	class ObjectstoAcquire;

	class AIProcess
	{
	public:
		enum class FADE_STATE : std::int32_t
		{
			kNormal = 0,
			kIn = 1,
			kOut = 2,
			kTeleportIn = 3,
			kTeleportOut = 4,
			kOutDisable = 5,
			kOutDelete = 6
		};

		enum class HEAD_TRACK_TYPE : std::int32_t
		{
			kDefault = 0,
			kAction = 1,
			kCombat = 2,
			kDialog = 3,
			kScript = 4,
			kProcedure = 5,
			kTotal = 6
		};

		void AddToProcedureIndexRunning(Actor* a_actor, std::int32_t a_number)
		{
			using FuncType = decltype(&AIProcess::AddToProcedureIndexRunning);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::AddToProcedureIndexRunning };
			FUNC(this, a_actor, a_number);
		}

		void ComputeLastTimeProcessed()
		{
			using FuncType = decltype(&AIProcess::ComputeLastTimeProcessed);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::ComputeLastTimeProcessed };
			FUNC(this);
		}

		[[nodiscard]] REX::Float32 GetActorLightLevel()
		{
			using FuncType = decltype(&AIProcess::GetActorLightLevel);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::GetActorLightLevel };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] COMMAND_TYPE GetCommandType() const
		{
			using FuncType = decltype(&AIProcess::GetCommandType);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::GetCommandType };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] TESAmmo* GetCurrentAmmo(BGSEquipIndex a_equipIndex) const
		{
			using FuncType = decltype(&AIProcess::GetCurrentAmmo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::GetCurrentAmmo };
			return std::invoke(FUNC, this, a_equipIndex);
		}

		[[nodiscard]] ObjectRefHandle GetOccupiedFurniture() const
		{
			using FuncType = decltype(&AIProcess::GetOccupiedFurniture);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::GetOccupiedFurniture };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] TESPackage* GetPackageThatIsRunning() const
		{
			using FuncType = decltype(&AIProcess::GetPackageThatIsRunning);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::GetPackageThatIsRunning };
			return std::invoke(FUNC, this);
		}

		[[nodiscard]] bool IsWeaponSubgraphFinishedLoading(const Actor& a_actor) const
		{
			using FuncType = decltype(&AIProcess::IsWeaponSubgraphFinishedLoading);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::IsWeaponSubgraphFinishedLoading };
			return std::invoke(FUNC, this, a_actor);
		}

		void KnockExplosion(Actor* a_actor, const NiPoint3& a_location, REX::Float32 a_magnitude)
		{
			using FuncType = decltype(&AIProcess::KnockExplosion);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::KnockExplosion };
			FUNC(this, a_actor, a_location, a_magnitude);
		}

		bool PlayIdle(Actor& a_actor, TESIdleForm* a_idle, TESObjectREFR* a_target)
		{
			return SetupSpecialIdle(a_actor, DEFAULT_OBJECT::kActionIdle, a_idle, true, a_target);
		}

		bool ProcessGreet(Actor* a_actor, DIALOGUE_TYPE a_type, DIALOGUE_SUBTYPE a_subType, TESObjectREFR* a_target, BGSDialogueBranch* a_branch, bool a_forceSub, bool a_stop, bool a_que, bool a_sayCallback)
		{
			using FuncType = decltype(&AIProcess::ProcessGreet);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::ProcessGreet };
			return std::invoke(FUNC, this, a_actor, a_type, a_subType, a_target, a_branch, a_forceSub, a_stop, a_que, a_sayCallback);
		}

		bool RequestLoadAnimationsForWeaponChange(Actor& a_actor)
		{
			using FuncType = decltype(&AIProcess::RequestLoadAnimationsForWeaponChange);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::RequestLoadAnimationsForWeaponChange };
			return std::invoke(FUNC, this, a_actor);
		}

		void SetActorsDetectionEvent(Actor* a_actor, const NiPoint3& a_location, std::int32_t a_soundLevel, TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&AIProcess::SetActorsDetectionEvent);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetActorsDetectionEvent };
			FUNC(this, a_actor, a_location, a_soundLevel, a_ref);
		}

		void SetCommandType(COMMAND_TYPE a_type)
		{
			using FuncType = decltype(&AIProcess::SetCommandType);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetCommandType };
			FUNC(this, a_type);
		}

		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
		{
			using FuncType = decltype(&AIProcess::SetCurrentAmmo);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetCurrentAmmo };
			FUNC(this, a_equipIndex, a_ammo);
		}

		void SetEquippedItem(Actor* a_actor, const BGSObjectInstance& a_instance, const BGSEquipSlot* a_slot)
		{
			using FuncType = decltype(&AIProcess::SetEquippedItem);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetEquippedItem };
			FUNC(this, a_actor, a_instance, a_slot);
		}

		void SetRunOncePackage(TESPackage* a_package, Actor* a_actor)
		{
			using FuncType = decltype(&AIProcess::SetRunOncePackage);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetRunOncePackage };
			FUNC(this, a_package, a_actor);
		}

		bool SetWeaponBonesCulled(const Actor& a_actor, bool a_stateToSet, WEAPON_CULL_TYPE a_weaponCullType)
		{
			using FuncType = decltype(&AIProcess::SetWeaponBonesCulled);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetWeaponBonesCulled };
			return std::invoke(FUNC, this, a_actor, a_stateToSet, a_weaponCullType);
		}

		bool SetupSpecialIdle(Actor& a_actor, DEFAULT_OBJECT a_defaultObject, TESIdleForm* a_idle, bool a_testConditions, TESObjectREFR* a_targetOverride)
		{
			using FuncType = decltype(&AIProcess::SetupSpecialIdle);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::SetupSpecialIdle };
			return std::invoke(FUNC, this, a_actor, a_defaultObject, a_idle, a_testConditions, a_targetOverride);
		}

		void StopCurrentIdle(Actor* a_actor, bool a_instant, bool a_killFlavor)
		{
			using FuncType = decltype(&AIProcess::StopCurrentIdle);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::AIProcess::StopCurrentIdle };
			FUNC(this, a_actor, a_instant, a_killFlavor);
		}

		// members
		MiddleLowProcessData* middleLow;				   // 00
		MiddleHighProcessData* middleHigh;				   // 08
		HighProcessData* high;							   // 10
		ActorPackage currentPackage;					   // 18
		REX::Float32 hourLastProcessed;					   // 48
		REX::Float32 timeAdjustmentsMade;				   // 4C
		std::uint32_t dateLastProcessed;				   // 50
		CachedValues* cachedValues;						   // 58
		std::int32_t numberItemsActivate;				   // 60
		BSSimpleList<ObjectstoAcquire*> objectList;		   // 68
		BSSimpleList<TESObjectREFR*> genericLocationsList; // 78
		ObjectstoAcquire* acquireObject;				   // 88
		ObjectstoAcquire* savedAcquireObject;			   // 90
		REX::Float32 essentialDownTimer;				   // 98
		REX::Float32 deathTime;							   // 9C
		REX::Float32 trackedDamage;						   // A0
		TESBoundObject* itemBeingUsed;					   // A8
		AITimer combatDelayTimer;						   // B0
		ObjectRefHandle followTarget;					   // B8
		ObjectRefHandle target;							   // BC
		ObjectRefHandle genericLocation;				   // C0
		ObjectRefHandle genericSecondLocation;			   // C4
		BGSListForm* targetFormList;					   // C8
		std::uint32_t currentSpeakingTopicID;			   // D0
		ObjectRefHandle patrolLocation;					   // D4
		ObjectRefHandle idleTarget;						   // D8
		std::int16_t formListNumb;						   // DC
		std::uint8_t lowProcessFlags;					   // DE
		std::uint8_t processLevel;						   // DF
		bool skippedTimeStampForPathing;				   // E0
		bool ignoringCombat;							   // E1
		bool endAlarmOnActor;							   // E2
		bool escortingPlayer;							   // E3
		bool updateEditorDeadModel;						   // E4
		bool editorDeadActive;							   // E5
		bool initializingPosition;						   // E6
	};
	static_assert(sizeof(AIProcess) == 0xE8);
}
