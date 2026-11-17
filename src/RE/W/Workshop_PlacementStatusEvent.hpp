#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE::Workshop
{
	enum class PlacementStatusValue : std::int32_t;

	class PlacementStatusEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<PlacementStatusEvent>*
		{
			using FuncType = decltype(&PlacementStatusEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::Workshop::PlacementStatusEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Enum<PlacementStatusValue, std::int8_t> value; // 0x00
	};

	static_assert(sizeof(PlacementStatusEvent) == 0x01);
}
