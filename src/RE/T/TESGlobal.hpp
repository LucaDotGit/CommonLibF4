#pragma once

#include "RE/B/BSString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) TESGlobal : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESGlobal;
		inline static constexpr const auto& VTABLE = VTABLE::TESGlobal;
		inline static constexpr auto FORM_TYPE = FormType::GlobalVariable;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				Deleted = 1 << 5,
				Constant = 1 << 6,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		[[nodiscard]]
		auto GetValue() const noexcept -> REX::Float32
		{
			return value;
		}

		void SetValue(REX::Float32 a_value) noexcept
		{
			value = a_value;
		}

		void ModValue(REX::Float32 a_value) noexcept
		{
			value += a_value;
		}

		// members
		BSString formEditorID; // 0x20
		REX::Float32 value;	   // 0x30
	};

	static_assert(sizeof(TESGlobal) == 0x38);
}
