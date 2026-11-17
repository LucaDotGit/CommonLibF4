#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class GameVM;
	class HolotapeChatterEvent;
	class HolotapePlayEvent;
	class TESContainerChangedEvent;
	class TESEquipEvent;
}

namespace RE::BSScript
{
	class IVirtualMachine;
	class Object;
}

namespace RE::GameScript
{
	class HandlePolicy;
}

namespace RE::GameScript::Internal
{
	class InventoryFilter;
}

namespace RE::GameScript
{
	class __declspec(novtable) InventoryEventHandler :
		public BSTEventSink<HolotapeChatterEvent>,	   // 0x00
		public BSTEventSink<HolotapePlayEvent>,		   // 0x08
		public BSTEventSink<TESContainerChangedEvent>, // 0x10
		public BSTEventSink<TESEquipEvent>,			   // 0x18
		public BSTSingletonSDM<InventoryEventHandler>  // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__InventoryEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__InventoryEventHandler;

		~InventoryEventHandler() override; // 0x00

		// override (BSTEventSink<HolotapeChatterEvent>)
		auto ProcessEvent(
			const HolotapeChatterEvent& a_event,
			BSTEventSource<HolotapeChatterEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<HolotapePlayEvent>)
		auto ProcessEvent(
			const HolotapePlayEvent& a_event,
			BSTEventSource<HolotapePlayEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESContainerChangedEvent>)
		auto ProcessEvent(
			const TESContainerChangedEvent& a_event,
			BSTEventSource<TESContainerChangedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESEquipEvent>)
		auto ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> InventoryEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<InventoryEventHandler**>{ID::GameScript::InventoryEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;								   // 0x28
		HandlePolicy* handlePolicy;					   // 0x30
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x38
		mutable BSSpinLock inventoryFilterLock;		   // 0x40
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<Internal::InventoryFilter>>
			inventoryFilters; // 0x48
	};

	static_assert(sizeof(InventoryEventHandler) == 0x78);
}
