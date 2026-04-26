#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Workshop
{
	class BuildableAreaEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<BuildableAreaEvent>* GetEventSource()
		{
			using FuncType = decltype(&BuildableAreaEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::Workshop::BuildableAreaEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		bool exit; // 00
	};
	static_assert(sizeof(BuildableAreaEvent) == 0x01);
}
