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
	class __declspec(novtable) CombatEventHandler :
		public BSTEventSink<TESHitEvent>,			   // 0x00
		public BSTEventSink<TESMagicEffectApplyEvent>, // 0x08
		public BSTEventSink<BGSRadiationDamageEvent>,  // 0x10
		public BSTSingletonSDM<CombatEventHandler>	   // 0x18
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__CombatEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__CombatEventHandler;

		enum class BoolFilter : std::int32_t
		{
			DoNotCare = 0,
			True = 1,
			False = 2,

			_Count = 3
		};

		~CombatEventHandler() override; // 0x00

		// override (BSTEventSink<TESHitEvent>)
		auto ProcessEvent(const TESHitEvent& a_event, BSTEventSource<TESHitEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESMagicEffectApplyEvent>)
		auto ProcessEvent(
			const TESMagicEffectApplyEvent& a_event,
			BSTEventSource<TESMagicEffectApplyEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<BGSRadiationDamageEvent>)
		auto ProcessEvent(
			const BGSRadiationDamageEvent& a_event,
			BSTEventSource<BGSRadiationDamageEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> CombatEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<CombatEventHandler**>{ID::GameScript::CombatEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;												  // 0x20
		mutable BSSpinLock hitLock;																	  // 0x28
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::HitRegistrationList>> hitEvents; // 0x30
		mutable BSSpinLock magicEffectApplyLock;													  // 0x60
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::MagicEffectApplyRegistrationList>>
			magicEffectApplyEvents;				// 0x68
		mutable BSSpinLock radiationDamageLock; // 0x98
		BSTHashMap<BSScript::ObjectHandle, BSTSmartPointer<Internal::RadiationDamageRegistrationList>>
			radiationDamageEvents; // 0xA0
	};

	static_assert(sizeof(CombatEventHandler) == 0xD0);
}
