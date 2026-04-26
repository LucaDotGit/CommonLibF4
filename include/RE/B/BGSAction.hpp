#pragma once

#include "RE/B/BGSKeyword.hpp"

namespace RE
{
	class __declspec(novtable) BGSAction
		: public BGSKeyword // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAction };
		inline static constexpr auto VTABLE{ VTABLE::BGSAction };
		inline static constexpr auto FORM_TYPE{ FormType::kAction };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kRestricted = 1 << 15
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		std::uint32_t index; // 28
	};
	static_assert(sizeof(BGSAction) == 0x30);
}
