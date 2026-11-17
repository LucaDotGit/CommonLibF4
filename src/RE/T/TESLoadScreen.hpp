#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class LoadNIFData;

	class __declspec(novtable) TESLoadScreen : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLoadScreen;
		inline static constexpr const auto& VTABLE = VTABLE::TESLoadScreen;
		inline static constexpr auto FORM_TYPE = FormType::LoadScreen;

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
		TESCondition conditions;		// 0x20
		LoadNIFData* loadNIFData;		// 0x28
		BGSLocalizedString loadingText; // 0x30
	};

	static_assert(sizeof(TESLoadScreen) == 0x38);
}
