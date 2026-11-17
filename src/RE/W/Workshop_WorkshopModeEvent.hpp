#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::Workshop
{
	class WorkshopModeEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<WorkshopModeEvent>*
		{
			using FuncType = decltype(&WorkshopModeEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::WorkshopModeEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> workshopRef; // 0x00
		bool start;							  // 0x08
	};

	static_assert(sizeof(WorkshopModeEvent) == 0x10);
}
