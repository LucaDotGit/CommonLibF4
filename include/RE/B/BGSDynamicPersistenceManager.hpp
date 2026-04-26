#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class QueuedPromoteReferencesTask;

	class BGSDynamicPersistenceManager
		: public BSTSingletonExplicit<BGSDynamicPersistenceManager> // 00
	{
	public:
		[[nodiscard]] static BGSDynamicPersistenceManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSDynamicPersistenceManager**>{ ID::BGSDynamicPersistenceManager::Singleton };
			return *SINGLETON;
		}

		bool PromoteReference(TESObjectREFR* a_ref, TESForm* a_owner)
		{
			using FuncType = decltype(&BGSDynamicPersistenceManager::PromoteReference);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSDynamicPersistenceManager::PromoteReference };
			return std::invoke(FUNC, this, a_ref, a_owner);
		}

		bool DemoteReference(TESObjectREFR* a_ref, TESForm* a_owner, bool a_allowActors = false)
		{
			using FuncType = decltype(&BGSDynamicPersistenceManager::DemoteReference);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSDynamicPersistenceManager::DemoteReference };
			return std::invoke(FUNC, this, a_ref, a_owner, a_allowActors);
		}

		// members
		BSTArray<NiPointer<QueuedPromoteReferencesTask>> tasks; // 00
		mutable BSSpinLock tasksLock;							// 18
		volatile std::int32_t pauseCount;						// 20
	};
	static_assert(sizeof(BGSDynamicPersistenceManager) == 0x28);
}
