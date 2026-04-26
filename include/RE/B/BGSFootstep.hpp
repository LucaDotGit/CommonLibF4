#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSFootstep
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSFootstep };
		inline static constexpr auto VTABLE{ VTABLE::BGSFootstep };
		inline static constexpr auto FORM_TYPE{ FormType::kFootstep };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSFixedString tagString;	 // 20
		BGSImpactDataSet* impactSet; // 28
	};
	static_assert(sizeof(BGSFootstep) == 0x30);
}
