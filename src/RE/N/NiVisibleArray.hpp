#pragma once

#include "RE/S/SimpleArray.hpp"

namespace RE
{
	class BSGeometry;

	class NiVisibleArray
	{
	public:
		// members
		SimpleArray<BSGeometry*> array; // 0x00
		std::uint32_t currentSize;		// 0x08
		std::uint32_t allocatedSize;	// 0x0C
		std::uint32_t growBy;			// 0x10
	};

	static_assert(sizeof(NiVisibleArray) == 0x18);
}
