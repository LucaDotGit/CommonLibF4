#pragma once

#include "RE/B/BSTEvent.hpp"

namespace RE
{
	class BGSOnPlayerFallLongDistances
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSOnPlayerFallLongDistances>*
		{
			using FuncType = decltype(&BGSOnPlayerFallLongDistances::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOnPlayerFallLongDistances::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		REX::Float32 damage; // 0x00
	};

	static_assert(sizeof(BGSOnPlayerFallLongDistances) == 0x04);
}
