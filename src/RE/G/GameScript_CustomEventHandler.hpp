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
	class __declspec(novtable) CustomEventHandler : public BSTSingletonSDM<CustomEventHandler> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__CustomEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__CustomEventHandler;

		virtual ~CustomEventHandler(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> CustomEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<CustomEventHandler**>{ID::GameScript::CustomEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm; // 0x10
		mutable BSSpinLock customEventLock;			   // 0x18
		BSTHashMap<BSTSmartPointer<BSScript::Object>, BSTSmartPointer<Internal::CustomEventRelay>>
			customEventRelays; // 0x20
	};

	static_assert(sizeof(CustomEventHandler) == 0x50);
}
