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
	class __declspec(novtable) LOSEventHandler : public BSTSingletonSDM<LOSEventHandler> // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__LOSEventHandler;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__LOSEventHandler;

		virtual ~LOSEventHandler(); // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> LOSEventHandler*
		{
			static const auto SINGLETON =
				REL::Relocation<LOSEventHandler**>{ID::GameScript::LOSEventHandler::Singleton};
			return *SINGLETON;
		}

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> vm;				 // 0x10
		mutable BSSpinLock losLock;									 // 0x18
		BSTArray<BSTSmartPointer<Internal::LOSEventData>> losEvents; // 0x20
		std::uint32_t nextLOSEventID;								 // 0x38
	};

	static_assert(sizeof(LOSEventHandler) == 0x40);
}
