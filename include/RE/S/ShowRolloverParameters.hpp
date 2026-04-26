#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE::UserEvents
{
	enum class INPUT_CONTEXT_ID : std::int32_t;
}

namespace RE
{
	class ShowRolloverParameters
	{
	public:
		// members
		BSFixedString rolloverNoun;													// 00
		BSFixedString activateButtonText;											// 08
		BSFixedString activateButtonTextSecondary;									// 10
		bool activateButtonEnabled;													// 18
		bool secondaryButtonEnabled;												// 19
		bool holotape;																// 1A
		bool legendary;																// 1B
		bool taggedForSearch;														// 1C
		REX::Enum<UserEvents::INPUT_CONTEXT_ID, std::int32_t> inputContextOverride; // 20
	};
	static_assert(sizeof(ShowRolloverParameters) == 0x28);
}
