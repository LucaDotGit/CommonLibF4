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
			Begin = 0,
			End = 1
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESScenePhaseEvent>*
		{
			using FuncType = decltype(&TESScenePhaseEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESScenePhaseEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		TESFormID sceneFormID;										  // 0x00
		std::uint32_t phaseIndex;									  // 0x04
		REX::Enum<EventType, std::int32_t> eventType;				  // 0x08
		std::uint16_t questStageID;									  // 0x0C
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 0x10
	};

	static_assert(sizeof(TESScenePhaseEvent) == 0x18);
}
