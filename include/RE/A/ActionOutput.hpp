#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class TESIdleForm;

	class ActionOutput
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActionOutput };

		enum class ACTION_RESULTS : std::int32_t
		{
			kNotAllowed = -1
		};

		// members
		BSFixedString animEvent;	   // 00
		BSFixedString targetAnimEvent; // 08
		std::int32_t result;		   // 10
		TESIdleForm* sequence;		   // 18
		TESIdleForm* animObjIdle;	   // 20
		std::uint32_t sequenceIndex;   // 28
	};
	static_assert(sizeof(ActionOutput) == 0x30);
}
