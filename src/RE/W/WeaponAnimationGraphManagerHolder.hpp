#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/I/IAnimationGraphManagerHolder.hpp"

namespace RE
{
	class BSAnimationGraphEvent;
	class BSAnimationGraphManager;

	class __declspec(novtable) WeaponAnimationGraphManagerHolder :
		public IAnimationGraphManagerHolder,		// 0x00
		public BSTEventSink<BSAnimationGraphEvent>, // 0x08
		public BSIntrusiveRefCounted				// 0x10
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::WeaponAnimationGraphManagerHolder;
		inline static constexpr const auto& VTABLE = VTABLE::WeaponAnimationGraphManagerHolder;

		~WeaponAnimationGraphManagerHolder() override; // 0x00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		auto ProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource)
			-> BSEventNotifyControl override;

		// members
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager; // 0x08
		ObjectRefHandle owner;											// 0x10
	};

	static_assert(sizeof(WeaponAnimationGraphManagerHolder) == 0x28);
}
