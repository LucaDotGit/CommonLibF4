#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundKeywordMapping
		: public TESForm // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSSoundKeywordMapping };
		inline static constexpr auto VTABLE{ VTABLE::BGSSoundKeywordMapping };
		inline static constexpr auto FORM_TYPE{ FormType::kSoundKeywordMapping };

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
		BSTSet<BGSKeyword*> keywordSet;									  // 20
		BSTHashMap<std::uint32_t, BGSSoundDescriptorForm*> reverbDescMap; // 50
		BGSSoundDescriptorForm* descriptor;								  // 80
		BGSSoundDescriptorForm* exteriorTail;							  // 88
		BGSSoundDescriptorForm* vatsDescriptor;							  // 90
		REX::Float32 vatsDescThreshold;									  // 98
	};
	static_assert(sizeof(BGSSoundKeywordMapping) == 0xA0);
}
