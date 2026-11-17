#pragma once

#include "RE/B/BSPortal.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiTPointerList.hpp"

namespace RE
{
	class BSOcclusionShape;
	class BSPortal;
	class NiAVObject;

	class __declspec(novtable) BSPortalGraph : public NiRefObject // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSPortalGraph;
		inline static constexpr const auto& VTABLE = VTABLE::BSPortalGraph;

		~BSPortalGraph() override; // 0x00

		// members
		NiTPointerList<BSOcclusionShape*> occluderList;			  // 0x10
		NiTPointerList<BSPortal*> portalList;					  // 0x28
		BSTArray<NiPointer<BSMultiBoundRoom>> multiBoundRoomList; // 0x40
		BSTArray<NiPointer<NiAVObject>> alwayRenderChildren;	  // 0x58
		NiPointer<NiNode> portalNodeRoot;						  // 0x70
		BSTArray<NiPointer<NiAVObject>> attachAlwaysRenderQueue;  // 0x78
		BSTArray<NiPointer<NiAVObject>> detachAlwaysRenderQueue;  // 0x90
		BSTArray<NiPointer<NiNode>> unboundNodes;				  // 0xA8
		std::uint32_t worldID;									  // 0xC0
	};

	static_assert(sizeof(BSPortalGraph) == 0xC8);
}
