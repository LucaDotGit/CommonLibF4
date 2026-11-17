#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/C/CellAttachDetachEventSource.hpp"

namespace RE
{
	class CellAttachDetachEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			PreAttach = 0,
			PostAttach = 1,
			PreDetach = 2,
			PostDetach = 3
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<CellAttachDetachEvent>*
		{
			auto& singleton = CellAttachDetachEventSource::CellAttachDetachEventSourceSingleton::GetSingleton();
			return std::addressof(singleton.source);
		}

		// members
		TESObjectCELL* cell;						  // 0x00
		REX::Enum<EventType, std::int32_t> eventType; // 0x08
	};

	static_assert(sizeof(CellAttachDetachEvent) == 0x10);
}
