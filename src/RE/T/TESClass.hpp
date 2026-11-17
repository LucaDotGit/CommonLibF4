#pragma once

#include "RE/B/BGSPropertySheet.hpp"
#include "RE/C/CLASS_DATA.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESClass :
		public TESForm,			// 0x00
		public TESFullName,		// 0x20
		public TESDescription,	// 0x30
		public TESTexture,		// 0x48
		public BGSPropertySheet // 0x58
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESClass;
		inline static constexpr const auto& VTABLE = VTABLE::TESClass;
		inline static constexpr auto FORM_TYPE = FormType::Class;

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				TagSkills = 1 << 1
			};
		};

		using ChangeFlags = ChangeFlag::ChangeFlags;

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
		CLASS_DATA data; // 0x68
	};

	static_assert(sizeof(TESClass) == 0x70);
}
