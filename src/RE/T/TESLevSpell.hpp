#pragma once

#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevSpell :
		public TESBoundObject, // 0x00
		public TESLeveledList  // 0x68
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLevSpell;
		inline static constexpr const auto& VTABLE = VTABLE::TESLevSpell;
		inline static constexpr auto FORM_TYPE = FormType::LeveledSpell;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;
	};

	static_assert(sizeof(TESLevSpell) == 0x98);
}
