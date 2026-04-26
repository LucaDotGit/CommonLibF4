#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSStringT.hpp"
#include "RE/I/IDLE_DATA.hpp"
#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class NiFormArray;

	class __declspec(novtable) TESIdleForm
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESIdleForm };
		inline static constexpr auto VTABLE{ VTABLE::TESIdleForm };
		inline static constexpr auto FORM_TYPE{ FormType::kIdle };

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
		TESCondition conditions;		 // 20
		IDLE_DATA data;					 // 28
		NiFormArray* childIdles;		 // 30
		TESIdleForm* parentIdle;		 // 38
		TESIdleForm* previousIdle;		 // 40
		BSFixedString behaviorGraphName; // 48
		BSFixedString animEventName;	 // 50
		BSFixedString animFileName;		 // 58
		BSString formEditorID;			 // 60
	};
	static_assert(sizeof(TESIdleForm) == 0x70);
}
