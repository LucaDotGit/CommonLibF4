#pragma once

#include "RE/B/BGSModelMaterialSwap.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) TESObjectANIO :
		public TESForm,				// 0x00
		public BGSModelMaterialSwap // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESObjectANIO;
		inline static constexpr const auto& VTABLE = VTABLE::TESObjectANIO;
		inline static constexpr auto FORM_TYPE = FormType::AnimObject;

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
		BSFixedString formEditorID;	   // 0x60
		BSFixedString unloadEventName; // 0x68
	};

	static_assert(sizeof(TESObjectANIO) == 0x70);
}
