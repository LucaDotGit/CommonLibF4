#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSemaphore.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTempEffect.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/P/PROCESS_TYPE.hpp"

namespace RE
{
	enum class PTYPE : std::int32_t;

	class Crime;
	class MuzzleFlash;
	class PositionPlayerEvent;
	class SyncQueueObj;

	class __declspec(novtable) ProcessLists
		: public BSTEventSink<PositionPlayerEvent>, // 000
		  public BSTSingletonSDM<ProcessLists>		// 008
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ProcessLists };
		inline static constexpr auto VTABLE{ VTABLE::ProcessLists };

		~ProcessLists() override; // 00

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent& a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override; // 01

		[[nodiscard]] static ProcessLists* GetSingleton();

		BSTArray<ActorHandle>& GetAllActorsByProcess(PROCESS_TYPE a_processLevel);
		const BSTArray<ActorHandle>& GetAllActorsByProcess(PROCESS_TYPE a_processLevel) const;

		BSContainer::ForEachResult ForEachActor(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<Actor>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachActorInProcess(PROCESS_TYPE a_processLevel,
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<Actor>&)>>& a_predicate) const;
		BSContainer::ForEachResult ForEachTempEffect(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<BSTempEffect>&)>>& a_predicate) const;

		[[nodiscard]] bool AreHostileActorsNear(BSScrapArray<ActorHandle>* a_hostileActorArray);
		[[nodiscard]] bool IsActorTargetingREFinPackage(const TESObjectREFR* a_actor, PTYPE a_type, bool a_onlyHigh);
		[[nodiscard]] std::int16_t RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_losCount);

		// members
		mutable BSSemaphore movementSyncSema;													   // 010
		REX::Float32 crimeUpdateTimer;															   // 018
		REX::Float32 removeExcessDeadTimer;														   // 01C
		std::int32_t numberHighActors;															   // 020
		std::int32_t numberFullyEnabledHighActors;												   // 024
		std::int32_t crimeNumber;																   // 028
		ActorHandle statdetect;																	   // 02C
		bool runDetection;																		   // 030
		bool showDetectionStats;																   // 031
		bool processHigh;																		   // 032
		bool processLow;																		   // 033
		bool processMHigh;																		   // 034
		bool processMLow;																		   // 035
		bool processSche;																		   // 036
		bool showSubtitle;																		   // 037
		bool updatingLowList;																	   // 038
		REX::Float32 secondsPassedNoProcess;													   // 03C
		BSTArray<ActorHandle> highActorHandles;													   // 040
		BSTArray<ActorHandle> lowActorHandles;													   // 058
		BSTArray<ActorHandle> middleHighActorHandles;											   // 070
		BSTArray<ActorHandle> middleLowActorHandles;											   // 088
		std::array<BSTArray<ActorHandle>*, std::to_underlying(PROCESS_TYPE::kTotal)> allProcesses; // 0A0
		std::array<BSSimpleList<Crime*>*, 7> globalCrimes;										   // 0C0
		BSTArray<NiPointer<BSTempEffect>> globalTempEffects;									   // 0F8
		mutable BSSpinLock globalEffectsLock;													   // 110
		BSTArray<NiPointer<BSTempEffect>> magicEffects;											   // 118
		mutable BSSpinLock magicEffectsLock;													   // 130
		BSTArray<NiPointer<BSTempEffect>> interfaceEffects;										   // 138
		mutable BSSpinLock interfaceEffectsLock;												   // 150
		BSSimpleList<MuzzleFlash*> referenceMuzzleFlashes;										   // 158
		BSTArray<ObjectRefHandle> tempShouldMoves;												   // 168
		BSSimpleList<ActorHandle> aliveActors;													   // 180
		BSSimpleList<ActorHandle> idleChatterActors;											   // 190
		BSSimpleList<ActorHandle> randomDialogueActors;											   // 1A0
		BSTArray<ActorHandle> initPackageLocationsQueue;										   // 1B0
		mutable BSSpinLock packageLocationsQueueLock;											   // 1C8
		BSTArray<ActorHandle> initAnimPositionQueue;											   // 1D0
		BSTArray<BSTSmartPointer<SyncQueueObj>> syncPositionQueue;								   // 1E8
		REX::Float32 playerActionCommentTimer;													   // 200
		REX::Float32 playerKnockObjectCommentTimer;												   // 204
		std::uint32_t currentLowActor;															   // 208
		std::uint32_t currentMiddleHighActor;													   // 20C
		std::uint32_t currentMiddleLowActor;													   // 210
		bool runSchedules;																		   // 214
		bool runMovement;																		   // 215
		bool runAnimations;																		   // 216
		bool updateActorsInPlayerCell;															   // 217
	};
	static_assert(sizeof(ProcessLists) == 0x218);
}
