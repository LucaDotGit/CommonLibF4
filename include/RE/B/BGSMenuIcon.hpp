#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESIcon.hpp"

namespace RE
{
	class __declspec(novtable) BGSMenuIcon
		: public TESForm, // 00
		  public TESIcon  // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSMenuIcon };
		inline static constexpr auto VTABLE{ VTABLE::BGSMenuIcon };
		inline static constexpr auto FORM_TYPE{ FormType::kMenuIcon };

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
	static_assert(sizeof(BGSMenuIcon) == 0x30);
}
