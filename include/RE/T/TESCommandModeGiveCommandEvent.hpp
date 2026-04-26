#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t;

	class TESCommandModeGiveCommandEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCommandModeGiveCommandEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCommandModeGiveCommandEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCommandModeGiveCommandEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceRef;				   // 00
		NiPointer<TESObjectREFR> targetRef;				   // 08
		REX::Enum<COMMAND_TYPE, std::int32_t> commandType; // 10
	};
	static_assert(sizeof(TESCommandModeGiveCommandEvent) == 0x18);
}
