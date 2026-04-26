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
			kBegin = 0,
			kEnd = 1
		};

		[[nodiscard]] static BSTEventSource<TESTopicInfoEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESTopicInfoEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESTopicInfoEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> speakerRef;						  // 00
		BSTSmartPointer<REFREventCallbacks::IEventCallback> callback; // 08
		TESFormID topicInfoFormID;									  // 10
		REX::Enum<EventType, std::int32_t> eventType;				  // 14
		std::uint32_t stage;										  // 18
	};
	static_assert(sizeof(TESTopicInfoEvent) == 0x20);
}
