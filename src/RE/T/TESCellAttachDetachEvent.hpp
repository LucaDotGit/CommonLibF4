#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESCellAttachDetachEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESCellAttachDetachEvent>*
		{
			using FuncType = decltype(&TESCellAttachDetachEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCellAttachDetachEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> cellRef; // 0x00
		bool attached;					  // 0x08
	};

	static_assert(sizeof(TESCellAttachDetachEvent) == 0x10);
}
