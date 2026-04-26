#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class BSNavmeshInfo;
	class BSPathingCell;

	class BSPathingLocation
	{
	public:
		// members
		NiPoint3 location;						   // 00
		BSNavmeshInfo* navMesh;					   // 10
		BSTArray<const BSNavmeshInfo*>* navMeshes; // 18
		BSTSmartPointer<BSPathingCell> cell;	   // 20
		std::uint16_t triangle;					   // 28
		std::uint8_t flags;						   // 2A
		std::uint8_t clientData;				   // 2B
	};
	static_assert(sizeof(BSPathingLocation) == 0x30);
}
