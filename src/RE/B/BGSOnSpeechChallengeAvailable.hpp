#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BGSOnSpeechChallengeAvailable
	{
	public:
		[[nodiscard]]
		static auto GetEventSource() -> BSTEventSource<BGSOnSpeechChallengeAvailable>*
		{
			using FuncType = decltype(&BGSOnSpeechChallengeAvailable::GetEventSource);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSOnSpeechChallengeAvailable::GetEventSource);
			return std::invoke(FUNC);
		}

		// members
		NiPointer<TESObjectREFR> ref; // 0x00
	};

	static_assert(sizeof(BGSOnSpeechChallengeAvailable) == 0x08);
}
