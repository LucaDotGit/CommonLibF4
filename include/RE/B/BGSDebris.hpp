#pragma once

#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSDebrisData;

	class __declspec(novtable) BGSDebris
		: public TESForm,		// 00
		  public BGSPreloadable // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDebris };
		inline static constexpr auto VTABLE{ VTABLE::BGSDebris };
		inline static constexpr auto FORM_TYPE{ FormType::kDebris };

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
		BSSimpleList<BGSDebrisData*> dataList; // 28
	};
	static_assert(sizeof(BGSDebris) == 0x38);
}
