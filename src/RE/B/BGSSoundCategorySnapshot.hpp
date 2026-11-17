#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundCategorySnapshot : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundCategorySnapshot;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundCategorySnapshot;
		inline static constexpr auto FORM_TYPE = FormType::SoundCategorySnapshot;

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
		BSTHashMap<BGSSoundCategory*, REX::Float32> categoryMult; // 0x20
		std::int8_t priority;									  // 0x50
	};

	static_assert(sizeof(BGSSoundCategorySnapshot) == 0x58);
}
