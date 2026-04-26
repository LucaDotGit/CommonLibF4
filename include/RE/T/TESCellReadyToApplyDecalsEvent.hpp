#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class TESCellReadyToApplyDecalsEvent
	{
	public:
		[[nodiscard]] static BSTEventSource<TESCellReadyToApplyDecalsEvent>* GetEventSource()
		{
			using FuncType = decltype(&TESCellReadyToApplyDecalsEvent::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::TESCellReadyToApplyDecalsEvent::GetEventSource };
			return std::invoke(FUNC);
		}

		// members
		TESObjectCELL* cell; // 00
	};
	static_assert(sizeof(TESCellReadyToApplyDecalsEvent) == 0x08);
}
