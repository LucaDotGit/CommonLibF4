#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSString.hpp"
#include "RE/I/IDLE_DATA.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiFormArray;

	class __declspec(novtable) TESIdleForm : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESIdleForm;
		inline static constexpr const auto& VTABLE = VTABLE::TESIdleForm;
		inline static constexpr auto FORM_TYPE = FormType::Idle;

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
		TESCondition conditions;		 // 0x20
		IDLE_DATA data;					 // 0x28
		NiFormArray* childIdles;		 // 0x30
		TESIdleForm* parentIdle;		 // 0x38
		TESIdleForm* previousIdle;		 // 0x40
		BSFixedString behaviorGraphName; // 0x48
		BSFixedString animEventName;	 // 0x50
		BSFixedString animFileName;		 // 0x58
		BSString formEditorID;			 // 0x60
	};

	static_assert(sizeof(TESIdleForm) == 0x70);
}
