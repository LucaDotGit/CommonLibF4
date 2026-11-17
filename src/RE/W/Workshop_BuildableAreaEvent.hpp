#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Workshop
{
	class BuildableAreaEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BuildableAreaEvent>*
		{
			using FuncType = decltype(&BuildableAreaEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::BuildableAreaEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		bool exit; // 0x00
	};

	static_assert(sizeof(BuildableAreaEvent) == 0x01);
}
