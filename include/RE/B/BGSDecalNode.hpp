#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"

namespace RE
{
	class BSTempEffect;

	class __declspec(novtable) BGSDecalNode
		: public NiNode
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSDecalNode };
		inline static constexpr auto VTABLE{ VTABLE::BGSDecalNode };
		inline static constexpr auto Ni_RTTI{ Ni_RTTI::BGSDecalNode };

		// members
		BSTArray<NiPointer<BSTempEffect>> decals;	 // 140
		BSTArray<std::uint32_t> decalCreationFrames; // 158
		bool skinnedNode;							 // 170
	};
	static_assert(sizeof(BGSDecalNode) == 0x180);
}
