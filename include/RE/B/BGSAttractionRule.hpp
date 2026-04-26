#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAttractionRule
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAttractionRule };
		inline static constexpr auto VTABLE{ VTABLE::BGSAttractionRule };
		inline static constexpr auto FORM_TYPE{ FormType::kAttractionRule };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		class ATTRACTION_RULE_DATA
		{
		public:
			// members
			REX::Float32 radius;   // 00
			REX::Float32 minDelay; // 04
			REX::Float32 maxDelay; // 08
			bool requiresLOS;	   // 0C
			bool combatTarget;	   // 0D
		};
		static_assert(sizeof(ATTRACTION_RULE_DATA) == 0x10);

		// members
		ATTRACTION_RULE_DATA data;	// 20
		BSFixedString formEditorID; // 30
	};
	static_assert(sizeof(BGSAttractionRule) == 0x38);
}
