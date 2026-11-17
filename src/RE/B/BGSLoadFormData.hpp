#pragma once

#include "RE/B/BGSChangeFlags.hpp"
#include "RE/B/BGSSaveLoadFormInfo.hpp"

namespace RE
{
	class BGSLoadFormData
	{
	public:
		// members
		std::uint32_t formID;			// 0x00
		std::uint32_t dataSize;			// 0x04
		std::uint32_t uncompressedSize; // 0x08
		TESForm* form;					// 0x10
		BGSChangeFlags changeFlags;		// 0x18
		BGSChangeFlags oldChangeFlags;	// 0x20
		std::uint16_t flags;			// 0x28
		BGSSaveLoadFormInfo formInfo;	// 0x30
		std::uint8_t version;			// 0x38
	};

	static_assert(sizeof(BGSLoadFormData) == 0x28);
}
