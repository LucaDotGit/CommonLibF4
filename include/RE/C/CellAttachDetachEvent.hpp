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
			kPreAttach = 0,
			kPostAttach = 1,
			kPreDetach = 2,
			kPostDetach = 3
		};

		[[nodiscard]] static BSTEventSource<CellAttachDetachEvent>* GetEventSource()
		{
			auto& singleton = CellAttachDetachEventSource::CellAttachDetachEventSourceSingleton::GetSingleton();
			return std::addressof(singleton.source);
		}

		// members
		TESObjectCELL* cell;						  // 00
		REX::Enum<EventType, std::int32_t> eventType; // 08
	};
	static_assert(sizeof(CellAttachDetachEvent) == 0x10);
}
