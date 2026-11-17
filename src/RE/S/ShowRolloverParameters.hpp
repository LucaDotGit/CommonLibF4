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
		BSFixedString rolloverNoun;													// 0x00
		BSFixedString activateButtonText;											// 0x08
		BSFixedString activateButtonTextSecondary;									// 0x10
		bool activateButtonEnabled;													// 0x18
		bool secondaryButtonEnabled;												// 0x19
		bool holotape;																// 0x1A
		bool legendary;																// 0x1B
		bool taggedForSearch;														// 0x1C
		REX::Enum<UserEvents::INPUT_CONTEXT_ID, std::int32_t> inputContextOverride; // 0x20
	};

	static_assert(sizeof(ShowRolloverParameters) == 0x28);
}
