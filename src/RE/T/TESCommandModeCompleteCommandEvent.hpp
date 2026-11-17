#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	enum class COMMAND_TYPE : std::int32_t;

	class TESCommandModeCompleteCommandEvent
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<TESCommandModeCompleteCommandEvent>*
		{
			using FuncType = decltype(&TESCommandModeCompleteCommandEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::TESCommandModeCompleteCommandEvent::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> sourceRef;				   // 0x00
		NiPointer<TESObjectREFR> targetRef;				   // 0x08
		REX::Enum<COMMAND_TYPE, std::int32_t> commandType; // 0x10
	};

	static_assert(sizeof(TESCommandModeCompleteCommandEvent) == 0x18);
}
