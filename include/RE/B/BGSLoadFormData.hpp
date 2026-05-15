#pragma once

#include "RE/B/BGSChangeFlags.hpp"
#include "RE/B/BGSSaveLoadFormInfo.hpp"

namespace RE
{
	class BGSLoadFormData
	{
	public:
		// members
		std::uint32_t formID;			// 00
		std::uint32_t dataSize;			// 04
		std::uint32_t uncompressedSize; // 08
		TESForm* form;					// 10
		BGSChangeFlags changeFlags;		// 18
		BGSChangeFlags oldChangeFlags;	// 20
		std::uint16_t flags;			// 28
		BGSSaveLoadFormInfo formInfo;	// 30
		std::uint8_t version;			// 38
	};
	static_assert(sizeof(BGSLoadFormData) == 0x28);
}
