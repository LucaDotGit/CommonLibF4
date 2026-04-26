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
	class __declspec(novtable) InventoryEventHandler
		: public BSTEventSink<HolotapeChatterEvent>,	 // 00
		  public BSTEventSink<HolotapePlayEvent>,		 // 08
		  public BSTEventSink<TESContainerChangedEvent>, // 10
		  public BSTEventSink<TESEquipEvent>,			 // 18
		  public BSTSingletonSDM<InventoryEventHandler>	 // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__InventoryEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__InventoryEventHandler };

		~InventoryEventHandler() override; // 00

		// override (BSTEventSink<HolotapeChatterEvent>)
		BSEventNotifyControl ProcessEvent(const HolotapeChatterEvent& a_event, BSTEventSource<HolotapeChatterEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<HolotapePlayEvent>)
		BSEventNotifyControl ProcessEvent(const HolotapePlayEvent& a_event, BSTEventSource<HolotapePlayEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESContainerChangedEvent>)
		BSEventNotifyControl ProcessEvent(const TESContainerChangedEvent& a_event, BSTEventSource<TESContainerChangedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESEquipEvent>)
		BSEventNotifyControl ProcessEvent(const TESEquipEvent& a_event, BSTEventSource<TESEquipEvent>* a_eventSource) override; // 01

		[[nodiscard]] static InventoryEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<InventoryEventHandler**>{ ID::GameScript::InventoryEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		GameVM* gameVM;																								// 28
		HandlePolicy* handlePolicy;																					// 30
		BSTSmartPointer<BSScript::IVirtualMachine> vm;																// 38
		mutable BSSpinLock inventoryFilterLock;																		// 40
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<Internal::InventoryFilter>> inventoryFilters; // 48
	};
	static_assert(sizeof(InventoryEventHandler) == 0x78);
}
