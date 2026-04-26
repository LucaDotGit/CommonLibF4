#include "RE/P/ProcessLists.hpp"

#include "RE/A/Actor.hpp"

namespace RE
{
	ProcessLists* ProcessLists::GetSingleton()
	{
		static const auto SINGLETON = REL::Relocation<ProcessLists**>{ ID::ProcessLists::Singleton };
		return *SINGLETON;
	}

	BSTArray<ActorHandle>& ProcessLists::GetAllActorsByProcess(PROCESS_TYPE a_processLevel)
	{
		REX::Assert(a_processLevel >= PROCESS_TYPE::kMin && a_processLevel <= PROCESS_TYPE::kMax);
		return *allProcesses[std::to_underlying(a_processLevel)];
	}

	const BSTArray<ActorHandle>& ProcessLists::GetAllActorsByProcess(PROCESS_TYPE a_processLevel) const
	{
		REX::Assert(a_processLevel >= PROCESS_TYPE::kMin && a_processLevel <= PROCESS_TYPE::kMax);
		return *allProcesses[std::to_underlying(a_processLevel)];
	}

	BSContainer::ForEachResult ProcessLists::ForEachActor(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<Actor>&)>>& a_predicate) const
	{
		for (const auto* processes : allProcesses) {
			if (!processes) {
				continue;
			}

			for (const auto& actorHandle : *processes) {
				if (actorHandle && std::invoke(*a_predicate, actorHandle.get()) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult ProcessLists::ForEachActorInProcess(PROCESS_TYPE a_processLevel,
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<Actor>&)>>& a_predicate) const
	{
		if (a_processLevel < PROCESS_TYPE::kMin || a_processLevel > PROCESS_TYPE::kMax) {
			return BSContainer::ForEachResult::kContinue;
		}

		const auto* processes = allProcesses[std::to_underlying(a_processLevel)];
		if (!processes) {
			return BSContainer::ForEachResult::kContinue;
		}

		for (const auto& actorHandle : *processes) {
			if (actorHandle && std::invoke(*a_predicate, actorHandle.get()) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	BSContainer::ForEachResult ProcessLists::ForEachTempEffect(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const NiPointer<BSTempEffect>&)>>& a_predicate) const
	{
		const auto effectLock = BSAutoLock(magicEffectsLock);

		for (const auto& effect : magicEffects) {
			if (effect && std::invoke(*a_predicate, effect) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}

	bool ProcessLists::AreHostileActorsNear(BSScrapArray<ActorHandle>* a_hostileActorArray)
	{
		using FuncType = decltype(&ProcessLists::AreHostileActorsNear);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ProcessLists::AreHostileActorsNear };
		return std::invoke(FUNC, this, a_hostileActorArray);
	}

	bool ProcessLists::IsActorTargetingREFinPackage(const TESObjectREFR* a_actor, PTYPE a_type, bool a_onlyHigh)
	{
		using FuncType = decltype(&ProcessLists::IsActorTargetingREFinPackage);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ProcessLists::IsActorTargetingREFinPackage };
		return std::invoke(FUNC, this, a_actor, a_type, a_onlyHigh);
	}

	std::int16_t ProcessLists::RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_LOSCount)
	{
		using FuncType = decltype(&ProcessLists::RequestHighestDetectionLevelAgainstActor);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ProcessLists::RequestHighestDetectionLevelAgainstActor };
		return std::invoke(FUNC, this, a_actor, a_LOSCount);
	}
}
