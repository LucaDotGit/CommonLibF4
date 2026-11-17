#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundTagSet : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundTagSet;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundTagSet;
		inline static constexpr auto FORM_TYPE = FormType::SoundTagSet;

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
		BSTHashMap<BSFixedString, BGSSoundDescriptorForm*> soundTags; // 0x20
	};

	static_assert(sizeof(BGSSoundTagSet) == 0x50);
}
