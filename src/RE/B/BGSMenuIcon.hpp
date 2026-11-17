#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESIcon.hpp"

namespace RE
{
	class __declspec(novtable) BGSMenuIcon :
		public TESForm, // 0x00
		public TESIcon	// 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSMenuIcon;
		inline static constexpr const auto& VTABLE = VTABLE::BGSMenuIcon;
		inline static constexpr auto FORM_TYPE = FormType::MenuIcon;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;
	};

	static_assert(sizeof(BGSMenuIcon) == 0x30);
}
