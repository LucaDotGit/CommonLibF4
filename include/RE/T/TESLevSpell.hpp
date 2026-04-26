#pragma once

#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevSpell
		: public TESBoundObject, // 00
		  public TESLeveledList	 // 68
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLevSpell };
		inline static constexpr auto VTABLE{ VTABLE::TESLevSpell };
		inline static constexpr auto FORM_TYPE{ FormType::kLeveledSpell };

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
	static_assert(sizeof(TESLevSpell) == 0x98);
}
