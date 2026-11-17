#pragma once

#include "RE/B/BSPointerHandleSmartPointer.hpp"
#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class WorkshopNPCTransferEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<WorkshopNPCTransferEvent>*
		{
			using FuncType = decltype(&WorkshopNPCTransferEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::WorkshopNPCTransferEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		ObjectRefHandlePtr npcRef;			// 0x00
		BGSLocation* location{nullptr};		// 0x08
		BGSKeyword* actionKeyword{nullptr}; // 0x10
	};

	static_assert(sizeof(WorkshopNPCTransferEvent) == 0x18);
}
