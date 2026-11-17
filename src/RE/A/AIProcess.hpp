#pragma once

#include "RE/A/AITimer.hpp"
#include "RE/A/ActorPackage.hpp"
#include "RE/B/BGSEquipIndex.hpp"
#include "RE/B/BGSObjectInstance.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/D/DEFAULT_OBJECT.hpp"

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
	class NiPoint3;
	class ObjectstoAcquire;

	class AIProcess
	{
	public:
		enum class FADE_STATE : std::int32_t
		{
			Normal = 0,
			In = 1,
			Out = 2,
			TeleportIn = 3,
			TeleportOut = 4,
			OutDisable = 5,
			OutDelete = 6
		};

		enum class HEAD_TRACK_TYPE : std::int32_t
		{
			Default = 0,
			Action = 1,
			Combat = 2,
			Dialog = 3,
			Script = 4,
			Procedure = 5,
			_Count = 6
		};

		void AddToProcedureIndexRunning(Actor* a_actor, std::int32_t a_number)
		{
			using FuncType = decltype(&AIProcess::AddToProcedureIndexRunning);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::AddToProcedureIndexRunning);
			std::invoke(FUNC, this, a_actor, a_number);
		}

		void ComputeLastTimeProcessed()
		{
			using FuncType = decltype(&AIProcess::ComputeLastTimeProcessed);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::ComputeLastTimeProcessed);
			std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetActorLightLevel() -> REX::Float32
		{
			using FuncType = decltype(&AIProcess::GetActorLightLevel);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetActorLightLevel);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetCommandType() const -> COMMAND_TYPE
		{
			using FuncType = decltype(&AIProcess::GetCommandType);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetCommandType);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetCurrentAmmo(BGSEquipIndex a_equipIndex) const -> TESAmmo*
		{
			using FuncType = decltype(&AIProcess::GetCurrentAmmo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetCurrentAmmo);
			return std::invoke(FUNC, this, a_equipIndex);
		}

		[[nodiscard]]
		auto GetCurrentAmmoCount(BGSEquipIndex a_equipIndex) const -> std::uint32_t
		{
			using FuncType = decltype(&AIProcess::GetCurrentAmmoCount);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetCurrentAmmoCount);
			return std::invoke(FUNC, this, a_equipIndex);
		}

		[[nodiscard]]
		auto GetOccupiedFurniture() const -> ObjectRefHandle
		{
			using FuncType = decltype(&AIProcess::GetOccupiedFurniture);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetOccupiedFurniture);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto GetPackageThatIsRunning() const -> TESPackage*
		{
			using FuncType = decltype(&AIProcess::GetPackageThatIsRunning);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::GetPackageThatIsRunning);
			return std::invoke(FUNC, this);
		}

		[[nodiscard]]
		auto IsWeaponSubgraphFinishedLoading(const Actor& a_actor) const -> bool
		{
			using FuncType = decltype(&AIProcess::IsWeaponSubgraphFinishedLoading);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::IsWeaponSubgraphFinishedLoading);
			return std::invoke(FUNC, this, a_actor);
		}

		void KnockExplosion(Actor* a_actor, const NiPoint3& a_location, REX::Float32 a_magnitude)
		{
			using FuncType = decltype(&AIProcess::KnockExplosion);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::KnockExplosion);
			std::invoke(FUNC, this, a_actor, a_location, a_magnitude);
		}

		auto PlayIdle(Actor& a_actor, TESIdleForm* a_idle, TESObjectREFR* a_target) -> bool
		{
			return SetupSpecialIdle(a_actor, DEFAULT_OBJECT::ActionIdle, a_idle, true, a_target);
		}

		auto ProcessGreet(
			Actor* a_actor,
			DIALOGUE_TYPE a_type,
			DIALOGUE_SUBTYPE a_subType,
			TESObjectREFR* a_target,
			BGSDialogueBranch* a_branch,
			bool a_forceSub,
			bool a_stop,
			bool a_que,
			bool a_sayCallback) -> bool
		{
			using FuncType = decltype(&AIProcess::ProcessGreet);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::ProcessGreet);
			return std::invoke(
				FUNC,
				this,
				a_actor,
				a_type,
				a_subType,
				a_target,
				a_branch,
				a_forceSub,
				a_stop,
				a_que,
				a_sayCallback);
		}

		auto RequestLoadAnimationsForWeaponChange(Actor& a_actor) -> bool
		{
			using FuncType = decltype(&AIProcess::RequestLoadAnimationsForWeaponChange);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::RequestLoadAnimationsForWeaponChange);
			return std::invoke(FUNC, this, a_actor);
		}

		void SetActorsDetectionEvent(
			Actor* a_actor,
			const NiPoint3& a_location,
			std::int32_t a_soundLevel,
			TESObjectREFR* a_ref)
		{
			using FuncType = decltype(&AIProcess::SetActorsDetectionEvent);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetActorsDetectionEvent);
			std::invoke(FUNC, this, a_actor, a_location, a_soundLevel, a_ref);
		}

		void SetCommandType(COMMAND_TYPE a_type)
		{
			using FuncType = decltype(&AIProcess::SetCommandType);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetCommandType);
			std::invoke(FUNC, this, a_type);
		}

		void SetCurrentAmmo(BGSEquipIndex a_equipIndex, TESAmmo* a_ammo)
		{
			using FuncType = decltype(&AIProcess::SetCurrentAmmo);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetCurrentAmmo);
			std::invoke(FUNC, this, a_equipIndex, a_ammo);
		}

		void SetCurrentAmmoCount(BGSEquipIndex a_equipIndex, std::uint32_t a_count)
		{
			using FuncType = decltype(&AIProcess::SetCurrentAmmoCount);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetCurrentAmmoCount);
			std::invoke(FUNC, this, a_equipIndex, a_count);
		}

		void SetEquippedItem(Actor* a_actor, const BGSObjectInstance& a_instance, const BGSEquipSlot* a_slot)
		{
			using FuncType = decltype(&AIProcess::SetEquippedItem);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetEquippedItem);
			std::invoke(FUNC, this, a_actor, a_instance, a_slot);
		}

		void SetRunOncePackage(TESPackage* a_package, Actor* a_actor)
		{
			using FuncType = decltype(&AIProcess::SetRunOncePackage);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetRunOncePackage);
			std::invoke(FUNC, this, a_package, a_actor);
		}

		auto SetWeaponBonesCulled(const Actor& a_actor, bool a_stateToSet, WEAPON_CULL_TYPE a_weaponCullType) -> bool
		{
			using FuncType = decltype(&AIProcess::SetWeaponBonesCulled);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetWeaponBonesCulled);
			return std::invoke(FUNC, this, a_actor, a_stateToSet, a_weaponCullType);
		}

		auto SetupSpecialIdle(
			Actor& a_actor,
			DEFAULT_OBJECT a_defaultObject,
			TESIdleForm* a_idle,
			bool a_testConditions,
			TESObjectREFR* a_targetOverride) -> bool
		{
			using FuncType = decltype(&AIProcess::SetupSpecialIdle);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::SetupSpecialIdle);
			return std::invoke(FUNC, this, a_actor, a_defaultObject, a_idle, a_testConditions, a_targetOverride);
		}

		void StopCurrentIdle(Actor* a_actor, bool a_instant, bool a_killFlavor)
		{
			using FuncType = decltype(&AIProcess::StopCurrentIdle);
			static const auto FUNC = REL::Relocation<FuncType>(ID::AIProcess::StopCurrentIdle);
			std::invoke(FUNC, this, a_actor, a_instant, a_killFlavor);
		}

		// members
		MiddleLowProcessData* middleLow;				   // 0x00
		MiddleHighProcessData* middleHigh;				   // 0x08
		HighProcessData* high;							   // 0x10
		ActorPackage currentPackage;					   // 0x18
		REX::Float32 hourLastProcessed;					   // 0x48
		REX::Float32 timeAdjustmentsMade;				   // 0x4C
		std::uint32_t dateLastProcessed;				   // 0x50
		CachedValues* cachedValues;						   // 0x58
		std::int32_t numberItemsActivate;				   // 0x60
		BSSimpleList<ObjectstoAcquire*> objectList;		   // 0x68
		BSSimpleList<TESObjectREFR*> genericLocationsList; // 0x78
		ObjectstoAcquire* acquireObject;				   // 0x88
		ObjectstoAcquire* savedAcquireObject;			   // 0x90
		REX::Float32 essentialDownTimer;				   // 0x98
		REX::Float32 deathTime;							   // 0x9C
		REX::Float32 trackedDamage;						   // 0xA0
		TESBoundObject* itemBeingUsed;					   // 0xA8
		AITimer combatDelayTimer;						   // 0xB0
		ObjectRefHandle followTarget;					   // 0xB8
		ObjectRefHandle target;							   // 0xBC
		ObjectRefHandle genericLocation;				   // 0xC0
		ObjectRefHandle genericSecondLocation;			   // 0xC4
		BGSListForm* targetFormList;					   // 0xC8
		std::uint32_t currentSpeakingTopicID;			   // 0xD0
		ObjectRefHandle patrolLocation;					   // 0xD4
		ObjectRefHandle idleTarget;						   // 0xD8
		std::int16_t formListNumb;						   // 0xDC
		std::uint8_t lowProcessFlags;					   // 0xDE
		std::uint8_t processLevel;						   // 0xDF
		bool skippedTimeStampForPathing;				   // 0xE0
		bool ignoringCombat;							   // 0xE1
		bool endAlarmOnActor;							   // 0xE2
		bool escortingPlayer;							   // 0xE3
		bool updateEditorDeadModel;						   // 0xE4
		bool editorDeadActive;							   // 0xE5
		bool initializingPosition;						   // 0xE6
	};

	static_assert(sizeof(AIProcess) == 0xE8);
}
