#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESOnPCDialogueTargetEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESOnPCDialogueTargetEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESOnPCDialogueTargetEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESOnPCDialogueTargetEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		NiPointer<TESObjectREFR> targetRef; // 00
	};
	static_assert(sizeof(TESOnPCDialogueTargetEvent) == 0x08);
}
