#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/T/TESForm.hpp"

namespace RE
{
	class __declspec(novtable) BGSSoundKeywordMapping : public TESForm // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSSoundKeywordMapping;
		inline static constexpr const auto& VTABLE = VTABLE::BGSSoundKeywordMapping;
		inline static constexpr auto FORM_TYPE = FormType::SoundKeywordMapping;

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
		BSTSet<BGSKeyword*> keywordSet;									  // 0x20
		BSTHashMap<std::uint32_t, BGSSoundDescriptorForm*> reverbDescMap; // 0x50
		BGSSoundDescriptorForm* descriptor;								  // 0x80
		BGSSoundDescriptorForm* exteriorTail;							  // 0x88
		BGSSoundDescriptorForm* vatsDescriptor;							  // 0x90
		REX::Float32 vatsDescThreshold;									  // 0x98
	};

	static_assert(sizeof(BGSSoundKeywordMapping) == 0xA0);
}
