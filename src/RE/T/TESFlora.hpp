#pragma once

#include "RE/T/TESObjectACTI.hpp"
#include "RE/T/TESProduceForm.hpp"

namespace RE
{
	class __declspec(novtable) TESFlora :
		public TESObjectACTI, // 0x000
		public TESProduceForm // 0x148
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESFlora;
		inline static constexpr const auto& VTABLE = VTABLE::TESFlora;
		inline static constexpr auto FORM_TYPE = FormType::Flora;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		~TESFlora() override; // 0x00
	};

	static_assert(sizeof(TESFlora) == 0x168);
}
