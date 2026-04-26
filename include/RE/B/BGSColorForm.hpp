#pragma once

#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) BGSColorForm
		: public TESForm,	 // 00
		  public TESFullName // 20
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSColorForm };
		inline static constexpr auto VTABLE{ VTABLE::BGSColorForm };
		inline static constexpr auto FORM_TYPE{ FormType::kColorForm };

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

		enum class Flags : std::uint32_t
		{
			kNone = 0,
			kPlayable = 1 << 0,
			kRemappingIndex = 1 << 1,
			kExtendedLUT = 1 << 2
		};

		// members
		union
		{
			std::uint32_t hexColor;
			REX::Float32 remappingIndex;
		}; // 30
		TESCondition conditions;				  // 38
		REX::EnumSet<Flags, std::uint32_t> flags; // 40
	};
	static_assert(sizeof(BGSColorForm) == 0x48);
}
