#pragma once

#include "RE/B/BGSKeyword.hpp"

namespace RE
{
	class __declspec(novtable) BGSLocationRefType : public BGSKeyword // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSLocationRefType;
		inline static constexpr const auto& VTABLE = VTABLE::BGSLocationRefType;
		inline static constexpr auto FORM_TYPE = FormType::LocationRefType;

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

	static_assert(sizeof(BGSLocationRefType) == 0x28);
}
