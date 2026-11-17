#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/N/NiNode.hpp"

namespace RE
{
	class BSTempEffect;

	class __declspec(novtable) BGSDecalNode : public NiNode
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSDecalNode;
		inline static constexpr const auto& VTABLE = VTABLE::BGSDecalNode;
		inline static constexpr auto Ni_RTTI = Ni_RTTI::BGSDecalNode;

		// members
		BSTArray<NiPointer<BSTempEffect>> decals;	 // 0x140
		BSTArray<std::uint32_t> decalCreationFrames; // 0x158
		bool skinnedNode;							 // 0x170
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BGSDecalNode) == 0x180);
#else
	static_assert(sizeof(BGSDecalNode) == 0x160);
#endif
}
