#pragma once

#include "RE/B/BSResource_Archive2_DataReader.hpp"
#include "RE/B/BSResource_ID.hpp"

namespace RE::BSResource::Archive2
{
	class RegisteredEvent
	{
	public:
		// members
		DataReader reader;			  // 0x00
		ID nameID;					  // 0x20
		const char* nameText;		  // 0x30
		std::uint32_t contentsFormat; // 0x38
		std::uint32_t fileCount;	  // 0x3C
	};

	static_assert(sizeof(RegisteredEvent) == 0x40);
}
