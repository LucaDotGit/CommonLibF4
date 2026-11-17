#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) TESWordOfPower :
		public TESForm,	   // 0x00
		public TESFullName // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESWordOfPower;
		inline static constexpr const auto& VTABLE = VTABLE::TESWordOfPower;
		inline static constexpr auto FORM_TYPE = FormType::WordOfPower;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BGSLocalizedString translation; // 0x30
	};

	static_assert(sizeof(TESWordOfPower) == 0x38);
}
