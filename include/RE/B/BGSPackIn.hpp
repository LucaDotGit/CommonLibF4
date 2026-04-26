#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSPackIn
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSPackIn };
		inline static constexpr auto VTABLE{ VTABLE::BGSPackIn };
		inline static constexpr auto FORM_TYPE{ FormType::kPackIn };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kPrefab = 1 << 9,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;
	};
	static_assert(sizeof(BGSPackIn) == 0x20);
}
