#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSFootstepSet : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSFootstepSet;
		inline static constexpr const auto& VTABLE = VTABLE::BGSFootstepSet;
		inline static constexpr auto FORM_TYPE = FormType::FootstepSet;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		std::array<BSTArray<BGSFootstep*>, 5> entries; // 0x20
	};

	static_assert(sizeof(BGSFootstepSet) == 0x98);
}
