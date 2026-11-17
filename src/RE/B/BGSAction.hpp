#pragma once

#include "RE/B/BGSKeyword.hpp"

namespace RE
{
	class __declspec(novtable) BGSAction : public BGSKeyword // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSAction;
		inline static constexpr const auto& VTABLE = VTABLE::BGSAction;
		inline static constexpr auto FORM_TYPE = FormType::Action;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12,
				Restricted = 1 << 15
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		// members
		std::uint32_t index; // 0x28
	};

	static_assert(sizeof(BGSAction) == 0x30);
}
