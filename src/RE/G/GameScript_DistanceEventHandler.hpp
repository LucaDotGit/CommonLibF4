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
	class __declspec(novtable) DistanceEventHandler : public BSTSingletonSDM<DistanceEventHandler> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__DistanceEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__DistanceEventHandler;

		virtual ~DistanceEventHandler(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> DistanceEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<DistanceEventHandler**>{ID::GameScript::DistanceEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;						   // 0x10
		mutable BSSpinLock distanceLock;									   // 0x18
		BSTArray<BSTSmartPointer<Internal::DistanceEventData>> distanceEvents; // 0x20
	};

	static_assert(sizeof(DistanceEventHandler) == 0x38);
}
