#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESBookReadEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESBookReadEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESBookReadEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESBookReadEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> bookRef; // 00
		TESFormID baseFormID;			  // 08
		ContainerID uniqueID;			  // 0C
	};
	static_assert(sizeof(TESBookReadEvent) == 0x10);
}
