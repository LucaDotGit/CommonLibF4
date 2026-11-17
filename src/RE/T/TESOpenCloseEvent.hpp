#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESOpenCloseEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESOpenCloseEvent>*
		{
			using FuncType = decltype(&TESOpenCloseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESOpenCloseEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceRef; // 0x00
		NiPointer<TESObjectREFR> targetRef; // 0x08
		bool opened;						// 0x10
	};

	static_assert(sizeof(TESOpenCloseEvent) == 0x18);
}
