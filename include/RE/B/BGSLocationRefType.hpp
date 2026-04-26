#pragma once

#include "RE/B/BGSKeyword.hpp"

namespace RE
{
	class __declspec(novtable) BGSLocationRefType
		: public BGSKeyword // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSLocationRefType };
		inline static constexpr auto VTABLE{ VTABLE::BGSLocationRefType };
		inline static constexpr auto FORM_TYPE{ FormType::kLocationRefType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;
	};
	static_assert(sizeof(BGSLocationRefType) == 0x28);
}
