#pragma once

#include "RE/B/BSPointerHandleSmartPointer.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class WorkshopNPCTransferEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<WorkshopNPCTransferEvent>* GetEventSource()
		{
			using FuncType = decltype(&WorkshopNPCTransferEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::WorkshopNPCTransferEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandlePtr npcRef;			  // 00
		BGSLocation* location{ nullptr };	  // 08
		BGSKeyword* actionKeyword{ nullptr }; // 10
	};
	static_assert(sizeof(WorkshopNPCTransferEvent) == 0x18);
}
