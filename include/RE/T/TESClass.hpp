#pragma once

#include "RE/B/BGSPropertySheet.hpp"
#include "RE/C/CLASS_DATA.hpp"
#include "RE/T/TESDescription.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESClass
		: public TESForm,		  // 00
		  public TESFullName,	  // 20
		  public TESDescription,  // 30
		  public TESTexture,	  // 48
		  public BGSPropertySheet // 58
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESClass };
		inline static constexpr auto VTABLE{ VTABLE::TESClass };
		inline static constexpr auto FORM_TYPE{ FormType::kClass };

		struct ChangeFlag
		{
			enum ChangeFlags : std::uint32_t
			{
				kTagSkills = 1 << 1
			};
		};
		using ChangeFlags = ChangeFlag::ChangeFlags;

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
		CLASS_DATA data; // 68
	};
	static_assert(sizeof(TESClass) == 0x70);
}
