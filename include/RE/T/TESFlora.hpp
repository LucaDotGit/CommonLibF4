#pragma once

#include "RE/T/TESObjectACTI.hpp"
#include "RE/T/TESProduceForm.hpp"

namespace RE
{
	class __declspec(novtable) TESFlora
		: public TESObjectACTI, // 000
		  public TESProduceForm // 148
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESFlora };
		inline static constexpr auto VTABLE{ VTABLE::TESFlora };
		inline static constexpr auto FORM_TYPE{ FormType::kFlora };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;
	};
	static_assert(sizeof(TESFlora) == 0x168);
}
