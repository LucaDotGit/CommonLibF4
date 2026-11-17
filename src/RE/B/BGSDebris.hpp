#pragma once

#include "RE/B/BGSPreloadable.hpp"
#include "RE/B/BSSimpleList.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class BGSDebrisData;

	class __declspec(novtable) BGSDebris :
		public TESForm,		  // 0x00
		public BGSPreloadable // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDebris;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDebris;
		inline static constexpr auto FORM_TYPE = FormType::Debris;

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
		BSSimpleList<BGSDebrisData*> dataList; // 0x28
	};

	static_assert(sizeof(BGSDebris) == 0x38);
}
