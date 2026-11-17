#pragma once

#include "RE/T/TESForm.hpp"
#include "RE/T/TESFullName.hpp"
#include "RE/T/TESTexture.hpp"

namespace RE
{
	class __declspec(novtable) TESEyes :
		public TESForm,		// 0x00
		public TESFullName, // 0x20
		public TESTexture	// 0x30
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESEyes;
		inline static constexpr const auto& VTABLE = VTABLE::TESEyes;
		inline static constexpr auto FORM_TYPE = FormType::Eyes;

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

		enum class Flags : std::uint8_t
		{
			None = 0,
			Playable = 1 << 0,
			NotMale = 1 << 1,
			NotFemale = 1 << 2
		};

		// members
		REX::EnumSet<Flags, std::uint8_t> flags; // 0x40
	};

	static_assert(sizeof(TESEyes) == 0x48);
}
