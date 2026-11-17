#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESSceneEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			Begin = 0,
			End = 1
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESSceneEvent>*
		{
			using FuncType = decltype(&TESSceneEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESSceneEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;						  // 0x00
		REX::Enum<EventType, std::int32_t> eventType; // 0x04
		std::uint16_t questStageID;					  // 0x08
	};

	static_assert(sizeof(TESSceneEvent) == 0x0C);
}
