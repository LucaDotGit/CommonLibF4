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
	class DistanceEventData;
}

namespace RE::GameScript
{
	class __declspec(novtable) DistanceEventHandler
		: public BSTSingletonSDM<DistanceEventHandler> // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameScript__DistanceEventHandler };
		inline static constexpr auto VTABLE{ VTABLE::GameScript__DistanceEventHandler };

		virtual ~DistanceEventHandler(); // 00

		[[nodiscard]] static DistanceEventHandler* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<DistanceEventHandler**>{ ID::GameScript::DistanceEventHandler::Singleton };
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;						   // 10
		mutable BSSpinLock distanceLock;									   // 18
		BSTArray<BSTSmartPointer<Internal::DistanceEventData>> distanceEvents; // 20
	};
	static_assert(sizeof(DistanceEventHandler) == 0x38);
}
