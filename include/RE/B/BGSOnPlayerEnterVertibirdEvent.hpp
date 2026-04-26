#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnPlayerEnterVertibirdEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BGSOnPlayerEnterVertibirdEvent>* GetEventSource()
		{
			using FuncType = decltype(&BGSOnPlayerEnterVertibirdEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSOnPlayerEnterVertibirdEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> vertibirdRef; // 00
	};
	static_assert(sizeof(BGSOnPlayerEnterVertibirdEvent) == 0x08);
}
