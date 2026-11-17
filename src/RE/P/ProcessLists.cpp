#include "RE/P/ProcessLists.hpp"

#include "RE/A/Actor.hpp"
#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	auto ProcessLists::GetSingleton() noexcept -> ProcessLists*
	{
		static const auto SINGLETON = REL::Relocation<ProcessLists**>(ID::ProcessLists::Singleton);
		return *SINGLETON;
	}

	auto ProcessLists::GetAllActorsByProcess(PROCESS_TYPE a_processLevel) -> BSTArray<ActorHandle>&
	{
		REX::Assert(a_processLevel >= PROCESS_TYPE::_Min && a_processLevel <= PROCESS_TYPE::_Max);
		return *allProcesses[REX::ToUnsigned(std::to_underlying(a_processLevel))];
	}

	auto ProcessLists::GetAllActorsByProcess(PROCESS_TYPE a_processLevel) const -> const BSTArray<ActorHandle>&
	{
		REX::Assert(a_processLevel >= PROCESS_TYPE::_Min && a_processLevel <= PROCESS_TYPE::_Max);
		return *allProcesses[REX::ToUnsigned(std::to_underlying(a_processLevel))];
	}

	auto ProcessLists::ForEachActor(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<Actor>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		for (const auto* processes : allProcesses) {
			if (!processes) {
				continue;
			}

			for (const auto& actor : *processes) {
				if (std::invoke(a_predicate.get(), actor.get()) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ProcessLists::ForEachActorInProcess(
		PROCESS_TYPE a_processLevel,
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<Actor>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		REX::Assert(a_processLevel >= PROCESS_TYPE::_Min && a_processLevel <= PROCESS_TYPE::_Max);

		const auto* processes = allProcesses[REX::ToUnsigned(std::to_underlying(a_processLevel))];
		if (!processes) {
			return BSContainer::ForEachResult::Continue;
		}

		for (const auto& actor : *processes) {
			if (std::invoke(a_predicate.get(), actor.get()) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ProcessLists::ForEachTempEffect(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<BSTempEffect>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		const auto effectLock = BSAutoSpinLock(magicEffectsLock);

		for (const auto& effect : magicEffects) {
			if (std::invoke(a_predicate.get(), effect) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}

	auto ProcessLists::AreHostileActorsNear(BSScrapArray<ActorHandle>* a_hostileActorArray) -> bool
	{
		using FuncType = decltype(&ProcessLists::AreHostileActorsNear);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ProcessLists::AreHostileActorsNear);
		return std::invoke(FUNC, this, a_hostileActorArray);
	}

	auto ProcessLists::IsActorTargetingREFinPackage(const TESObjectREFR* a_actor, PTYPE a_type, bool a_onlyHigh) -> bool
	{
		using FuncType = decltype(&ProcessLists::IsActorTargetingREFinPackage);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ProcessLists::IsActorTargetingREFinPackage);
		return std::invoke(FUNC, this, a_actor, a_type, a_onlyHigh);
	}

	auto ProcessLists::RequestHighestDetectionLevelAgainstActor(Actor* a_actor, std::uint32_t& a_losCount)
		-> std::int16_t
	{
		using FuncType = decltype(&ProcessLists::RequestHighestDetectionLevelAgainstActor);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ProcessLists::RequestHighestDetectionLevelAgainstActor);
		return std::invoke(FUNC, this, a_actor, a_losCount);
	}
}
