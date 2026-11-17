#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE::REFREventCallbacks
{
	class IEventCallback;
}

namespace RE
{
	class TESTopicInfoEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			Begin = 0,
			End = 1
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESTopicInfoEvent>*
		{
			using FuncType = decltype(&TESTopicInfoEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESTopicInfoEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> speakerRef;						  // 0x00
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 0x08
		TESFormID topicInfoFormID;									  // 0x10
		REX::Enum<EventType, std::int32_t> eventType;				  // 0x14
		std::uint32_t stage;										  // 0x18
	};

	static_assert(sizeof(TESTopicInfoEvent) == 0x20);
}
