#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAttractionRule : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAttractionRule;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAttractionRule;
		inline static constexpr auto FORM_TYPE = FormType::AttractionRule;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		class ATTRACTION_RULE_DATA
		{
		public:
			// members
			REX::Float32 radius;   // 0x00
			REX::Float32 minDelay; // 0x04
			REX::Float32 maxDelay; // 0x08
			bool requiresLOS;	   // 0x0C
			bool combatTarget;	   // 0x0D
		};

		static_assert(sizeof(ATTRACTION_RULE_DATA) == 0x10);

		// members
		ATTRACTION_RULE_DATA data;	// 0x20
		BSFixedString formEditorID; // 0x30
	};

	static_assert(sizeof(BGSAttractionRule) == 0x38);
}
