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

	class __declspec(novtable) WeaponAnimationGraphManagerHolder
		: public IAnimationGraphManagerHolder,		  // 00
		  public BSTEventSink<BSAnimationGraphEvent>, // 08
		  public BSIntrusiveRefCounted				  // 10
	{
	public:
		inline static constexpr auto RTTI{ RTTI::WeaponAnimationGraphManagerHolder };
		inline static constexpr auto VTABLE{ VTABLE::WeaponAnimationGraphManagerHolder };

		~WeaponAnimationGraphManagerHolder() override; // 00

		// override (BSTEventSink<BSAnimationGraphEvent>)
		BSEventNotifyControl ProcessEvent(const BSAnimationGraphEvent& a_event, BSTEventSource<BSAnimationGraphEvent>* a_eventSource) override;

		// members
		BSTSmartPointer<BSAnimationGraphManager> animationGraphManager; // 08
		ObjectRefHandle owner;											// 10
	};
	static_assert(sizeof(WeaponAnimationGraphManagerHolder) == 0x28);
}
