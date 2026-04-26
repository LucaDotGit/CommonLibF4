#pragma once

#include "RE/B/BGSDualCastDataDEF.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSDualCastData
		: public TESBoundObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDualCastData };
		inline static constexpr auto VTABLE{ VTABLE::BGSDualCastData };
		inline static constexpr auto FORM_TYPE{ FormType::kDualCastData };

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
		BGSDualCastDataDEF data; // 68
	};
	static_assert(sizeof(BGSDualCastData) == 0x98);
}
