#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSFootstepSet
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSFootstepSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSFootstepSet };
		inline static constexpr auto FORM_TYPE{ FormType::kFootstepSet };

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
		std::array<BSTArray<BGSFootstep*>, 5> entries; // 20
	};
	static_assert(sizeof(BGSFootstepSet) == 0x98);
}
