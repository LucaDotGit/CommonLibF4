#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) TESWordOfPower
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESWordOfPower };
		inline static constexpr auto VTABLE{ VTABLE::TESWordOfPower };
		inline static constexpr auto FORM_TYPE{ FormType::kWordOfPower };

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
		BGSLocalizedString translation; // 30
	};
	static_assert(sizeof(TESWordOfPower) == 0x38);
}
