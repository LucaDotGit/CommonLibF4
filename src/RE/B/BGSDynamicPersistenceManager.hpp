#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class QueuedPromoteReferencesTask;

	class BGSDynamicPersistenceManager : public BSTSingletonExplicit<BGSDynamicPersistenceManager> // 0x00
	{
	public:
		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSDynamicPersistenceManager*
		{
			static const auto SINGLETON =
				REL::Relocation<BGSDynamicPersistenceManager**>{ID::BGSDynamicPersistenceManager::Singleton};
			return *SINGLETON;
		}

		auto PromoteReference(TESObjectREFR* a_ref, TESForm* a_owner) -> bool
		{
			using FuncType = decltype(&BGSDynamicPersistenceManager::PromoteReference);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSDynamicPersistenceManager::PromoteReference);
			return std::invoke(FUNC, this, a_ref, a_owner);
		}

		auto DemoteReference(TESObjectREFR* a_ref, TESForm* a_owner, bool a_allowActors = false) -> bool
		{
			using FuncType = decltype(&BGSDynamicPersistenceManager::DemoteReference);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSDynamicPersistenceManager::DemoteReference);
			return std::invoke(FUNC, this, a_ref, a_owner, a_allowActors);
		}

		// members
		BSTArray<NiPointer<QueuedPromoteReferencesTask>> tasks; // 0x00
		mutable BSSpinLock tasksLock;							// 0x18
		volatile std::int32_t pauseCount;						// 0x20
	};

	static_assert(sizeof(BGSDynamicPersistenceManager) == 0x28);
}
