#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
	class Object;
}

namespace RE::GameScript::Internal
{
	class CustomEventRelay;
}

namespace RE::GameScript
{
	class __declspec(novtable) CustomEventHandler
		: public BSTSingletonSDM<CustomEventHandler> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__CustomEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__CustomEventHandler };

		virtual ~CustomEventHandler(); // 00

		[[nodiscard]] static CustomEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<CustomEventHandler**>{ ID::GameScript::CustomEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;																  // 10
		mutable BSSpinLock customEventLock;																			  // 18
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<Internal::CustomEventRelay>> customEventRelays; // 20
	};
	static_assert(sizeof(CustomEventHandler) == 0x50);
}
