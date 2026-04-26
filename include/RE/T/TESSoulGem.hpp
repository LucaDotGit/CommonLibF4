#pragma once

#include "RE/T/TESObjectMISC.hpp"

namespace RE
{
	class __declspec(novtable) TESSoulGem
		: public TESObjectMISC // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESSoulGem };
		inline static constexpr auto VTABLE{ VTABLE::TESSoulGem };
		inline static constexpr auto FORM_TYPE{ FormType::kSoulGem };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12,
				kCanHoldNPCSoul = 1 << 17
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		TESSoulGem* linkedSoulGem; // 168
		std::int8_t currentSoul;   // 170
		std::uint8_t soulCapacity; // 171
	};
	static_assert(sizeof(TESSoulGem) == 0x178);
}
