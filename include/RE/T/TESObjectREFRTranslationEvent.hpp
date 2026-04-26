#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class TESObjectREFRTranslationEvent
	{
	public:
		enum class EventType : std::int32_t
		{
			kFail = 0,
			kSuccess = 1,
			kAlmostDone = 2
		};

		[[nodiscard]] static BSTEventSource<TESObjectREFRTranslationEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESObjectREFRTranslationEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESObjectREFRTranslationEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref;				  // 00
		REX::Enum<EventType, std::int32_t> eventType; // 08
	};
	static_assert(sizeof(TESObjectREFRTranslationEvent) == 0x10);
}
