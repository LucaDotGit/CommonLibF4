#pragma once

#include "RE/B/BSFixedString.hpp"

namespace RE
{
	class TESIdleForm;

	class ActionOutput
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ActionOutput;

		enum class ACTION_RESULTS : std::int32_t
		{
			NotAllowed = -1
		};

		// members
		BSFixedString animEvent;	   // 0x00
		BSFixedString targetAnimEvent; // 0x08
		std::int32_t result;		   // 0x10
		TESIdleForm* sequence;		   // 0x18
		TESIdleForm* animObjIdle;	   // 0x20
		std::uint32_t sequenceIndex;   // 0x28
	};

	static_assert(sizeof(ActionOutput) == 0x30);
}
