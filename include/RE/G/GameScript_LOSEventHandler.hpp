#pragma once

#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
}

namespace RE::GameScript::Internal
{
	class LOSEventData;
}

namespace RE::GameScript
{
	class __declspec(novtable) LOSEventHandler
		: public BSTSingletonSDM<LOSEventHandler> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__LOSEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__LOSEventHandler };

		virtual ~LOSEventHandler(); // 00

		[[nodiscard]] static LOSEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<LOSEventHandler**>{ ID::GameScript::LOSEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;				 // 10
		mutable BSSpinLock losLock;									 // 18
		BSTArray<BSTSmartPointer<Internal::LOSEventData>> losEvents; // 20
		std::uint32_t nextLOSEventID;								 // 38
	};
	static_assert(sizeof(LOSEventHandler) == 0x40);
}
