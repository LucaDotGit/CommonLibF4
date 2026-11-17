#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class BSNavmeshInfo;
	class BSPathingCell;

	class BSPathingLocation
	{
	public:
		// members
		NiPoint3 location;						   // 0x00
		BSNavmeshInfo* navMesh;					   // 0x10
		BSTArray<const BSNavmeshInfo*>* navMeshes; // 0x18
		BSTSmartPointer<BSPathingCell> cell;	   // 0x20
		std::uint16_t triangle;					   // 0x28
		std::uint8_t flags;						   // 0x2A
		std::uint8_t clientData;				   // 0x2B
	};

	static_assert(sizeof(BSPathingLocation) == 0x30);
}
