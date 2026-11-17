#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESGrabReleaseEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESGrabReleaseEvent>*
		{
			using FuncType = decltype(&TESGrabReleaseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESGrabReleaseEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> targetRef; // 0x00
		bool grabbed;						// 0x08
	};

	static_assert(sizeof(TESGrabReleaseEvent) == 0x10);
}
