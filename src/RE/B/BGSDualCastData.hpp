#pragma once

#include "RE/B/BGSDualCastDataDEF.hpp"
#include "RE/T/TESBoundObject.hpp"

namespace RE
{
	class __declspec(novtable) BGSDualCastData : public TESBoundObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDualCastData;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDualCastData;
		inline static constexpr auto FORM_TYPE = FormType::DualCastData;

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
		BGSDualCastDataDEF data; // 0x68
	};

	static_assert(sizeof(BGSDualCastData) == 0x98);
}
