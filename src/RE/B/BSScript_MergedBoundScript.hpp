#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class BoundScript;

	class MergedBoundScript
	{
	public:
		// members
		BSTSmartPointer<BoundScript> childScript;  // 0x00
		BSTSmartPointer<BoundScript> parentScript; // 0x08
	};

	static_assert(sizeof(MergedBoundScript) == 0x10);
}
