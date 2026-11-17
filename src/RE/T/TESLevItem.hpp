#pragma once

#include "RE/B/BGSLocalizedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESBoundObject.hpp"
#include "RE/T/TESLeveledList.hpp"

namespace RE
{
	class __declspec(novtable) TESLevItem :
		public TESBoundObject, // 0x00
		public TESLeveledList  // 0x68
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESLevItem;
		inline static constexpr const auto& VTABLE = VTABLE::TESLevItem;
		inline static constexpr auto FORM_TYPE = FormType::LeveledItem;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]]
		static auto GetOverrideNameMap() noexcept -> auto&
		{
			static const auto OVERRIDE_NAME_MAP = REL::Relocation<BSTHashMap<TESLevItem*, BGSLocalizedString>*>{
				ID::TESLevItem::OverrideNameMap,
				Offset::TESLevItem::OverrideNameMap
			};
			return *OVERRIDE_NAME_MAP;
		}
	};

	static_assert(sizeof(TESLevItem) == 0x98);
}
