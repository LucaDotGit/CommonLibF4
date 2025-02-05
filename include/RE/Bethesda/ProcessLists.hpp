#pragma once

#include "RE/Bethesda/Actor.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSSemaphore.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTList.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/BSTempEffect.hpp"

namespace RE
{
	class Crime;
	class SyncQueueObj;

	class __declspec(novtable) ProcessLists
		: public BSTEventSink<PositionPlayerEvent>, // 000
		  public BSTSingletonSDM<ProcessLists>		// 008
	{
	public:
		enum PROCESS_LEVEL : std::uint8_t
		{
			kProcessLevel_High = 0,
			kProcessLevel_MiddleHigh = 1,
			kProcessLevel_MiddleLow = 2,
			kProcessLevel_Low = 3,

			kProcessLevel_Min = kProcessLevel_High,
			kProcessLevel_Max = kProcessLevel_Low,
			kProcessLevel_Count = 4
		};

	public:
		inline static constexpr auto RTTI{ RTTI::ProcessLists };
		inline static constexpr auto VTABLE{ VTABLE::ProcessLists };

		virtual ~ProcessLists(); // 00

		// override
		virtual BSEventNotifyControl ProcessEvent(const PositionPlayerEvent&, BSTEventSource<PositionPlayerEvent>*) override; // 01

		[[nodiscard]] static ProcessLists* GetSingleton()
		{
			static REL::Relocation<ProcessLists**> singleton{ REL::RelocationID(1569706, 2688869) };
			return *singleton;
		}

		BSTArray<ActorHandle>& GetAllActorsByProcess(PROCESS_LEVEL a_processLevel)
		{
			assert(a_processLevel <= kProcessLevel_Max);
			return *allProcesses[a_processLevel];
		}

		const BSTArray<ActorHandle>& GetAllActorsByProcess(PROCESS_LEVEL a_processLevel) const
		{
			assert(a_processLevel <= kProcessLevel_Max);
			return *allProcesses[a_processLevel];
		}

		BSContainer::ForEachResult ForEachActor(std::function<BSContainer::ForEachResult(Actor*)> a_callback) const;
		BSContainer::ForEachResult ForEachActorInProcess(PROCESS_LEVEL a_processLevel, std::function<BSContainer::ForEachResult(Actor*)> a_callback) const;
		BSContainer::ForEachResult ForEachHighActor(std::function<BSContainer::ForEachResult(Actor*)> a_callback) const;
		BSContainer::ForEachResult ForEachMagicTempEffect(std::function<BSContainer::ForEachResult(BSTempEffect*)> a_callback) const;
		BSContainer::ForEachResult ForEachModelEffect(std::function<BSContainer::ForEachResult(ModelReferenceEffect*)> a_callback) const;
		BSContainer::ForEachResult ForEachShaderEffect(std::function<BSContainer::ForEachResult(ShaderReferenceEffect*)> a_callback) const;

		[[nodiscard]] bool AreHostileActorsNear(BSScrapArray<ActorHandle>* a_hostileActorArray)
		{
			using func_t = decltype(&ProcessLists::AreHostileActorsNear);
			static REL::Relocation<func_t> func{ REL::RelocationID(1053584, 2234105) };
			return func(this, a_hostileActorArray);
		}

		[[nodiscard]] bool IsActorTargetingREFinPackage(const TESObjectREFR* a_actor, PTYPE a_type, bool a_onlyHigh)
		{
			using func_t = decltype(&ProcessLists::IsActorTargetingREFinPackage);
			static REL::Relocation<func_t> func{ REL::RelocationID(559542, 2234033) };
			return func(this, a_actor, a_type, a_onlyHigh);
		}

		[[nodiscard]] std::int16_t RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_LOSCount)
		{
			using func_t = decltype(&ProcessLists::RequestHighestDetectionLevelAgainstActor);
			static REL::Relocation<func_t> func{ REL::RelocationID(1036693, 2234111) };
			return func(this, a_actor, a_LOSCount);
		}

		// members
		BSSemaphore movementSyncSema;							   // 010
		float crimeUpdateTimer;									   // 018
		float removeExcessDeadTimer;							   // 01C
		std::int32_t numberHighActors;							   // 020
		std::int32_t numberFullyEnabledHighActors;				   // 024
		std::int32_t crimeNumber;								   // 028
		ActorHandle statdetect;									   // 02C
		bool runDetection;										   // 030
		bool showDetectionStats;								   // 031
		bool processHigh;										   // 032
		bool processLow;										   // 033
		bool processMHigh;										   // 034
		bool processMLow;										   // 035
		bool processSche;										   // 036
		bool showSubtitle;										   // 037
		bool updatingLowList;									   // 038
		float secondsPassedNoProcess;							   // 03C
		BSTArray<ActorHandle> highActorHandles;					   // 040
		BSTArray<ActorHandle> lowActorHandles;					   // 058
		BSTArray<ActorHandle> middleHighActorHandles;			   // 070
		BSTArray<ActorHandle> middleLowActorHandles;			   // 088
		BSTArray<ActorHandle>* allProcesses[kProcessLevel_Count];  // 0A0
		BSSimpleList<Crime*>* globalCrimes[7];					   // 0C0
		BSTArray<NiPointer<BSTempEffect>> globalTempEffects;	   // 0F8
		mutable BSSpinLock globalEffectsLock;					   // 110
		BSTArray<NiPointer<BSTempEffect>> magicEffects;			   // 118
		mutable BSSpinLock magicEffectsLock;					   // 130
		BSTArray<NiPointer<BSTempEffect>> interfaceEffects;		   // 138
		mutable BSSpinLock interfaceEffectsLock;				   // 150
		BSSimpleList<MuzzleFlash*> referenceMuzzleFlashes;		   // 158
		BSTArray<ObjectRefHandle> tempShouldMoves;				   // 168
		BSSimpleList<ActorHandle> aliveActors;					   // 180
		BSSimpleList<ActorHandle> idleChatterActors;			   // 190
		BSSimpleList<ActorHandle> randomDialogueActors;			   // 1A0
		BSTArray<ActorHandle> initPackageLocationsQueue;		   // 1B0
		mutable BSSpinLock packageLocationsQueueLock;			   // 1C8
		BSTArray<ActorHandle> initAnimPositionQueue;			   // 1D0
		BSTArray<BSTSmartPointer<SyncQueueObj>> syncPositionQueue; // 1E8
		float playerActionCommentTimer;							   // 200
		float playerKnockObjectCommentTimer;					   // 204
		std::uint32_t currentLowActor;							   // 208
		std::uint32_t currentMiddleHighActor;					   // 20C
		std::uint32_t currentMiddleLowActor;					   // 210
		bool runSchedules;										   // 214
		bool runMovement;										   // 215
		bool runAnimations;										   // 216
		bool updateActorsInPlayerCell;							   // 217
	};
	static_assert(sizeof(ProcessLists) == 0x218);
}
