#pragma once

#include "RE/T/TESObjectMISC.hpp"

namespace RE
{
	class __declspec(novtable) TESSoulGem : public TESObjectMISC // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESSoulGem;
		inline static constexpr const auto& VTABLE = VTABLE::TESSoulGem;
		inline static constexpr auto FORM_TYPE = FormType::SoulGem;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				CanHoldNPCSoul = 1 << 17
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESSoulGem() override; // 0x00

		// members
		TESSoulGem* linkedSoulGem; // 0x168
		std::int8_t currentSoul;   // 0x170
		std::uint8_t soulCapacity; // 0x171
	};

	static_assert(sizeof(TESSoulGem) == 0x178);
}
