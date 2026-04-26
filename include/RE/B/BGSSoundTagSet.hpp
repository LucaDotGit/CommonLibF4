#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundTagSet
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundTagSet };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundTagSet };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundTagSet };

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
		BSTHashMap<BSFixedString, BGSSoundDescriptorForm*> soundTags; // 20
	};
	static_assert(sizeof(BGSSoundTagSet) == 0x50);
}
