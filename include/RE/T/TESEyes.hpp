#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESEyes
		: public TESForm,	  // 00
		  public TESFullName, // 20
		  public TESTexture	  // 30
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESEyes };
		inline static constexpr auto VTABLE{ VTABLE::TESEyes };
		inline static constexpr auto FORM_TYPE{ FormType::kEyes };

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				kNonPlayable = 1 << 2,
				kDeleted = 1 << 5,
				kIgnored = 1 << 12
			};
		};
		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint8_t
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kNotMale = 1 << 1,
			kNotFemale = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 40
	};
	static_assert(sizeof(TESEyes) == 0x48);
}
