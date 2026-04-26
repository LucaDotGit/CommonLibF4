#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class WorkshopModeEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<WorkshopModeEvent>* GetEventSource()
		{
			using FuncType = decltype(&WorkshopModeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::WorkshopModeEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 00
		bool start;							  // 08
	};
	static_assert(sizeof(WorkshopModeEvent) == 0x10);
}
