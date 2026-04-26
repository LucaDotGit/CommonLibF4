#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class BGSRadiationDamageEvent;
	class TESHitEvent;
	class TESMagicEffectApplyEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript::Internal
{
	class HitRegistrationList;
	class MagicEffectApplyRegistrationList;
	class RadiationDamageRegistrationList;
}

namespace RE::GameScript
{
	class __declspec(novtable) CombatEventHandler
		: public BSTEventSink<TESHitEvent>,				 // 00
		  public BSTEventSink<TESMagicEffectApplyEvent>, // 08
		  public BSTEventSink<BGSRadiationDamageEvent>,	 // 10
		  public BSTSingletonSDM<CombatEventHandler>	 // 18
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__CombatEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__CombatEventHandler };

		enum class BoolFilter : std::int32_t
		{
			kDoNotCare = 0,
			kTrue = 1,
			kFalse = 2,

			kTotal = 3
		};

		~CombatEventHandler() override; // 00

		// override (BSTEventSink<TESHitEvent>)
		BSEventNotifyControl ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESMagicEffectApplyEvent>)
		BSEventNotifyControl ProcessEvent(const TESMagicEffectApplyEvent& a_event, BSTEventSource<TESMagicEffectApplyEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<BGSRadiationDamageEvent>)
		BSEventNotifyControl ProcessEvent(const BGSRadiationDamageEvent& a_event, BSTEventSource<BGSRadiationDamageEvent>* a_eventSource) override; // 01

		[[nodiscard]] static CombatEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<CombatEventHandler**>{ ID::GameScript::CombatEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;																			// 20
		mutable BSSpinLock hitLock;																								// 28
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::HitRegistrationList>> hitEvents;							// 30
		mutable BSSpinLock magicEffectApplyLock;																				// 60
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::MagicEffectApplyRegistrationList>> magicEffectApplyEvents; // 68
		mutable BSSpinLock radiationDamageLock;																					// 98
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::RadiationDamageRegistrationList>> radiationDamageEvents;	// A0
	};
	static_assert(sizeof(CombatEventHandler) == 0xD0);
}
