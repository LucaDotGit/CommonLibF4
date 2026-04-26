#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundCategorySnapshot
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundCategorySnapshot };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundCategorySnapshot };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundCategorySnapshot };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		// members
		BSTHashMap<BGSSoundCategory*, REX::Float32> categoryMult; // 20
		std::int8_t priority;									  // 50
	};
	static_assert(sizeof(BGSSoundCategorySnapshot) == 0x58);
}
