#pragma once

#include "RE/B/BSStringT.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) TESGlobal
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESGlobal };
		inline static constexpr auto VTABLE{ VTABLE::TESGlobal };
		inline static constexpr auto FORM_TYPE{ FormType::kGlobalVariable };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kDeleted = 1 << 5,
				kConstant = 1 << 6,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]] REX::Float32 GetValue() const noexcept { return value; }
		void SetValue(REX::Float32 a_value) noexcept { value = a_value; }
		void ModValue(REX::Float32 a_value) noexcept { value += a_value; }

		// members
		BSString formEditorID; // 20
		REX::Float32 value;	   // 30
	};
	static_assert(sizeof(TESGlobal) == 0x38);
}
