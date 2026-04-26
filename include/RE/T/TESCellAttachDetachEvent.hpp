#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESCellAttachDetachEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCellAttachDetachEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCellAttachDetachEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCellAttachDetachEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> cellRef; // 00
		bool attached;					  // 08
	};
	static_assert(sizeof(TESCellAttachDetachEvent) == 0x10);
}
