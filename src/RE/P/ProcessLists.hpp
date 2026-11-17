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

	class __declspec(novtable) ProcessLists :
		public BSTEventSink<PositionPlayerEvent>, // 0x000
		public BSTSingletonSDM<ProcessLists>	  // 0x008
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ProcessLists;
		inline static constexpr const auto& VTABLE = VTABLE::ProcessLists;

		~ProcessLists() override; // 0x00

		// override (BSTEventSink<PositionPlayerEvent>)
		auto ProcessEvent(
			const PositionPlayerEvent& a_event,
			BSTEventSource<PositionPlayerEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> ProcessLists*;

		auto GetAllActorsByProcess(PROCESS_TYPE a_processLevel) -> BSTArray<ActorHandle>&;
		auto GetAllActorsByProcess(PROCESS_TYPE a_processLevel) const -> const BSTArray<ActorHandle>&;

		auto ForEachActor(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<Actor>&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachActorInProcess(
			PROCESS_TYPE a_processLevel,
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<Actor>&) const>>&
				a_predicate) const -> BSContainer::ForEachResult;

		auto ForEachTempEffect(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<BSTempEffect>&)
														   const>>& a_predicate) const -> BSContainer::ForEachResult;

		[[nodiscard]]
		auto AreHostileActorsNear(BSScrapArray<ActorHandle>* a_hostileActorArray) -> bool;
		[[nodiscard]]
		auto IsActorTargetingREFinPackage(const TESObjectREFR* a_actor, PTYPE a_type, bool a_onlyHigh) -> bool;
		[[nodiscard]]
		auto RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_losCount) -> std::int16_t;

		// members
		mutable BSSemaphore movementSyncSema;													   // 0x010
		REX::Float32 crimeUpdateTimer;															   // 0x018
		REX::Float32 removeExcessDeadTimer;														   // 0x01C
		std::int32_t numberHighActors;															   // 0x020
		std::int32_t numberFullyEnabledHighActors;												   // 0x024
		std::int32_t crimeNumber;																   // 0x028
		ActorHandle statdetect;																	   // 0x02C
		bool runDetection;																		   // 0x030
		bool showDetectionStats;																   // 0x031
		bool processHigh;																		   // 0x032
		bool processLow;																		   // 0x033
		bool processMHigh;																		   // 0x034
		bool processMLow;																		   // 0x035
		bool processSche;																		   // 0x036
		bool showSubtitle;																		   // 0x037
		bool updatingLowList;																	   // 0x038
		REX::Float32 secondsPassedNoProcess;													   // 0x03C
		BSTArray<ActorHandle> highActorHandles;													   // 0x040
		BSTArray<ActorHandle> lowActorHandles;													   // 0x058
		BSTArray<ActorHandle> middleHighActorHandles;											   // 0x070
		BSTArray<ActorHandle> middleLowActorHandles;											   // 0x088
		std::array<BSTArray<ActorHandle>*, std::to_underlying(PROCESS_TYPE::_Count)> allProcesses; // 0x0A0
		std::array<BSSimpleList<Crime*>*, 7> globalCrimes;										   // 0x0C0
		BSTArray<NiPointer<BSTempEffect>> globalTempEffects;									   // 0x0F8
		mutable BSSpinLock globalEffectsLock;													   // 0x110
		BSTArray<NiPointer<BSTempEffect>> magicEffects;											   // 0x118
		mutable BSSpinLock magicEffectsLock;													   // 0x130
		BSTArray<NiPointer<BSTempEffect>> interfaceEffects;										   // 0x138
		mutable BSSpinLock interfaceEffectsLock;												   // 0x150
		BSSimpleList<MuzzleFlash*> referenceMuzzleFlashes;										   // 0x158
		BSTArray<ObjectRefHandle> tempShouldMoves;												   // 0x168
		BSSimpleList<ActorHandle> aliveActors;													   // 0x180
		BSSimpleList<ActorHandle> idleChatterActors;											   // 0x190
		BSSimpleList<ActorHandle> randomDialogueActors;											   // 0x1A0
		BSTArray<ActorHandle> initPackageLocationsQueue;										   // 0x1B0
		mutable BSSpinLock packageLocationsQueueLock;											   // 0x1C8
		BSTArray<ActorHandle> initAnimPositionQueue;											   // 0x1D0
		BSTArray<BSTSmartPointer<SyncQueueObj>> syncPositionQueue;								   // 0x1E8
		REX::Float32 playerActionCommentTimer;													   // 0x200
		REX::Float32 playerKnockObjectCommentTimer;												   // 0x204
		std::uint32_t currentLowActor;															   // 0x208
		std::uint32_t currentMiddleHighActor;													   // 0x20C
		std::uint32_t currentMiddleLowActor;													   // 0x210
		bool runSchedules;																		   // 0x214
		bool runMovement;																		   // 0x215
		bool runAnimations;																		   // 0x216
		bool updateActorsInPlayerCell;															   // 0x217
	};

	static_assert(sizeof(ProcessLists) == 0x218);
}
