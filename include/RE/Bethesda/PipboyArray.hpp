#pragma once

#include "RE/Bethesda/PipboyValue.hpp"

namespace RE
{
	class PipboyArray
		: public PipboyValue // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PipboyArray };
		inline static constexpr auto VTABLE{ VTABLE::PipboyArray };

		// members
		BSTArray<PipboyValue*> elements;		   // 18
		BSTSet<std::uint32_t> addedElementIDs;	   // 30
		BSTArray<std::uint32_t> removedElementIDs; // 60
		bool newlyCreated;						   // 78
	};
	static_assert(sizeof(PipboyArray) == 0x80);
}
