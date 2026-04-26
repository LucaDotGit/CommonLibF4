#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevItem
		: public TESBoundObject, // 00
		  public TESLeveledList	 // 68
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESLevItem };
		inline static constexpr auto VTABLE{ VTABLE::TESLevItem };
		inline static constexpr auto FORM_TYPE{ FormType::kLeveledItem };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] static auto& GetOverrideNameMap()
		{
			static const auto OVERRIDE_NAME_MAP = REL::Relocation<BSTHashMap<TESLevItem*, BGSLocalizedString>*>{ ID::TESLevItem::OverrideNameMap, Offset::TESLevItem::OverrideNameMap };
			return *OVERRIDE_NAME_MAP;
		}
	};
	static_assert(sizeof(TESLevItem) == 0x98);
}
