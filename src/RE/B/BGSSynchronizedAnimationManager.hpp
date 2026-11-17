#pragma once

#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class AnimationDataCleanupEvent;
	class AnimationDataSetupEvent;
	class BGSSynchronizedAnimationInstance;

	class __declspec(novtable) BGSSynchronizedAnimationManager :
		public BSTEventSink<AnimationDataSetupEvent>,			// 0x00
		public BSTEventSink<AnimationDataCleanupEvent>,			// 0x08
		public BSTSingletonSDM<BGSSynchronizedAnimationManager> // 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSynchronizedAnimationManager;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSynchronizedAnimationManager;

		~BGSSynchronizedAnimationManager() override; // 0x00

		// override (BSTEventSink<AnimationDataSetupEvent>)
		auto ProcessEvent(
			const AnimationDataSetupEvent& a_event,
			BSTEventSource<AnimationDataSetupEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<AnimationDataCleanupEvent>)
		auto ProcessEvent(
			const AnimationDataCleanupEvent& a_event,
			BSTEventSource<AnimationDataCleanupEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> BGSSynchronizedAnimationManager*
		{
			static const auto SINGLETON =
				REL::Relocation<BGSSynchronizedAnimationManager**>{ID::BGSSynchronizedAnimationManager::Singleton};
			return *SINGLETON;
		}

		[[nodiscard]]
		auto IsReferenceInSynchronizedScene(ObjectRefHandle a_ref) -> bool
		{
			using FuncType = decltype(&BGSSynchronizedAnimationManager::IsReferenceInSynchronizedScene);
			static const auto FUNC =
				REL::Relocation<FuncType>{ID::BGSSynchronizedAnimationManager::IsReferenceInSynchronizedScene};
			return std::invoke(FUNC, this, a_ref);
		}

		// members
		BSTArray<BSTSmartPointer<BGSSynchronizedAnimationInstance>> currentSynchAnims; // 0x18
		mutable BSReadWriteLock synchAnimsLock;										   // 0x30
		std::int32_t atomicSyncLock;												   // 0x38
		mutable BSSpinLock internalsLock;											   // 0x3C
	};

	static_assert(sizeof(BGSSynchronizedAnimationManager) == 0x48);
}
