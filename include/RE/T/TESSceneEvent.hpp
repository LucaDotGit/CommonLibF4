#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESSceneEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kBegin = 0,
			kEnd = 1
		};

		[[nodiscard]] static BSTEventSource<TESSceneEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESSceneEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESSceneEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;						  // 00
		REX::Enum<EventType, std::int32_t> eventType; // 04
		std::uint16_t questStageID;					  // 08
	};
	static_assert(sizeof(TESSceneEvent) == 0x0C);
}
