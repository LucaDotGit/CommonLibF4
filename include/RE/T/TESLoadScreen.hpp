#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class LoadNIFData;

	class __declspec(novtable) TESLoadScreen
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLoadScreen };
		inline static constexpr auto VTABLE{ VTABLE::TESLoadScreen };
		inline static constexpr auto FORM_TYPE{ FormType::kLoadScreen };

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
		TESCondition conditions;		// 20
		LoadNIFData* loadNIFData;		// 28
		BGSLocalizedString loadingText; // 30
	};
	static_assert(sizeof(TESLoadScreen) == 0x38);
}
