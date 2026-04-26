#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/G/GameScript_Internal_BroadcastEventManager.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript
{
	class __declspec(novtable) TeleportEventHandler
		: public BSTSingletonSDM<TeleportEventHandler> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__TeleportEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__TeleportEventHandler };

		virtual ~TeleportEventHandler(); // 00

		[[nodiscard]] static TeleportEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<TeleportEventHandler**>{ ID::GameScript::TeleportEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 10
		Internal::BroadcastEventManager eventManager;  // 18
	};
	static_assert(sizeof(TeleportEventHandler) == 0x38);
}
