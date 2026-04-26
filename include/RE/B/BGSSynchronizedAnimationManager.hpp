#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class AnimationDataCleanupEvent;
	class AnimationDataSetupEvent;
	class BGSSynchronizedAnimationInstance;

	class __declspec(novtable) BGSSynchronizedAnimationManager
		: public BSTEventSink<AnimationDataSetupEvent>,			  // 00
		  public BSTEventSink<AnimationDataCleanupEvent>,		  // 08
		  public BSTSingletonSDM<BGSSynchronizedAnimationManager> // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSynchronizedAnimationManager };
		inline static constexpr auto VTABLE{ VTABLE::BGSSynchronizedAnimationManager };

		~BGSSynchronizedAnimationManager() override; // 00

		// override (BSTEventSink<AnimationDataSetupEvent>)
		BSEventNotifyControl ProcessEvent(const AnimationDataSetupEvent& a_event, BSTEventSource<AnimationDataSetupEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<AnimationDataCleanupEvent>)
		BSEventNotifyControl ProcessEvent(const AnimationDataCleanupEvent& a_event, BSTEventSource<AnimationDataCleanupEvent>* a_eventSource) override; // 01

		[[nodiscard]] static BGSSynchronizedAnimationManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<BGSSynchronizedAnimationManager**>{ ID::BGSSynchronizedAnimationManager::Singleton };
			return *SINGLETON;
		}

		[[nodiscard]] bool IsReferenceInSynchronizedScene(ObjectRefHandle a_ref)
		{
			using FuncType = decltype(&BGSSynchronizedAnimationManager::IsReferenceInSynchronizedScene);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSynchronizedAnimationManager::IsReferenceInSynchronizedScene };
			return std::invoke(FUNC, this, a_ref);
		}

		// members
		BSTArray<BSTSmartPointer<BGSSynchronizedAnimationInstance>> currentSynchAnims; // 18
		mutable BSReadWriteLock synchAnimsLock;										   // 30
		std::int32_t atomicSyncLock;												   // 38
		mutable BSSpinLock internalsLock;											   // 3C
	};
	static_assert(sizeof(BGSSynchronizedAnimationManager) == 0x48);
}
