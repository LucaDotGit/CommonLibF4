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
			Fail = 0,
			Success = 1,
			AlmostDone = 2
		};

		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESObjectREFRTranslationEvent>*
		{
			using FuncType = decltype(&TESObjectREFRTranslationEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESObjectREFRTranslationEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref;				  // 0x00
		REX::Enum<EventType, std::int32_t> eventType; // 0x08
	};

	static_assert(sizeof(TESObjectREFRTranslationEvent) == 0x10);
}
