#pragma once

#include "RE/T/TESCondition.hpp"
#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"

namespace RE
{
	class __declspec(novtable) BGSColorForm :
		public TESForm,	   // 0x00
		public TESFullName // 0x20
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSColorForm;
		inline static constexpr const auto& VTABLE = VTABLE::BGSColorForm;
		inline static constexpr auto FORM_TYPE = FormType::ColorForm;

		struct RecordFlag
		{
			enum RecordFlags : std::uint32_t
			{
				NonPlayable = 1 << 2,
				Deleted = 1 << 5,
				Ignored = 1 << 12
			};
		};

		using RecordFlags = RecordFlag::RecordFlags;

		enum class Flags : std::uint32_t
		{
			None = 0,
			Playable = 1 << 0,
			RemappingIndex = 1 << 1,
			ExtendedLUT = 1 << 2
		};

		// members
		union
		{
		public:
			std::uint32_t hexColor;
			REX::Float32 remappingIndex;
		}; // 0x30

		TESCondition conditions;				  // 0x38
		REX::EnumSet<Flags, std::uint32_t> flags; // 0x40
	};

	static_assert(sizeof(BGSColorForm) == 0x48);
}
