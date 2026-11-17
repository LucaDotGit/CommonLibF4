#pragma once

#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSPackIn : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSPackIn;
		inline static constexpr const auto& VTABLE = VTABLE::BGSPackIn;
		inline static constexpr auto FORM_TYPE = FormType::PackIn;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Prefab = 1 << 9,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;
	};

	static_assert(sizeof(BGSPackIn) == 0x20);
}
