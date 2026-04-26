#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESGrabReleaseEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESGrabReleaseEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESGrabReleaseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESGrabReleaseEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 00
		bool grabbed;						// 08
	};
	static_assert(sizeof(TESGrabReleaseEvent) == 0x10);
}
