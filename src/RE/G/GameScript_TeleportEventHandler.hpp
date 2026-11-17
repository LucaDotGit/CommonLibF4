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
	class __declspec(novtable) TeleportEventHandler : public BSTSingletonSDM<TeleportEventHandler> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__TeleportEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__TeleportEventHandler;

		virtual ~TeleportEventHandler(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> TeleportEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<TeleportEventHandler**>{ID::GameScript::TeleportEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x10
		Internal::BroadcastEventManager eventManager;  // 0x18
	};

	static_assert(sizeof(TeleportEventHandler) == 0x38);
}
