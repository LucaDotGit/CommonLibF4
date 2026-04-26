#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAssociationType
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSAssociationType };
		inline static constexpr auto VTABLE{ VTABLE::BGSAssociationType };
		inline static constexpr auto FORM_TYPE{ FormType::kAssociationType };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kFamily = 1 << 0
		};

		// members
		std::array<std::array<BSFixedStringCS, 2>, 2> associationLabel; // 20
		REX::EnumSet<Flags, std::uint32_t> flags;						// 40
	};
	static_assert(sizeof(BGSAssociationType) == 0x48);
}
