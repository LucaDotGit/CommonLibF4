#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSAssociationType : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAssociationType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAssociationType;
		inline static constexpr auto FORM_TYPE = FormType::AssociationType;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Family = 1 << 0
		};

		// members
		std::array<std::array<BSFixedStringCS, 2>, 2> associationLabel; // 0x20
		REX::EnumSet<Flags, std::uint32_t> flags;						// 0x40
	};

	static_assert(sizeof(BGSAssociationType) == 0x48);
}
