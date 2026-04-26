#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class TESScenePhaseEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kBegin = 0,
			kEnd = 1
		};

		[[nodiscard]] static BSTEventSource<TESScenePhaseEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESScenePhaseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESScenePhaseEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;										  // 00
		std::uint32_t phaseIndex;									  // 04
		REX::Enum<EventType, std::int32_t> eventType;				  // 08
		std::uint16_t questStageID;									  // 0C
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 10
	};
	static_assert(sizeof(TESScenePhaseEvent) == 0x18);
}
