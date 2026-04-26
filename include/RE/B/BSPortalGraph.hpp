#pragma once

#include "RE/B/BSPortal.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiTPointerList.hpp"

namespace RE
{
	class BSOcclusionShape;
	class BSPortal;
	class NiAVObject;

	class __declspec(novtable) BSPortalGraph
		: public NiRefObject // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSPortalGraph };
		inline static constexpr auto VTABLE{ VTABLE::BSPortalGraph };

		~BSPortalGraph() override; // 00

		// members
		NiTPointerList<BSOcclusionShape*> occluderList;			  // 10
		NiTPointerList<BSPortal*> portalList;					  // 28
		BSTArray<NiPointer<BSMultiBoundRoom>> multiBoundRoomList; // 40
		BSTArray<NiPointer<NiAVObject>> alwayRenderChildren;	  // 58
		NiPointer<NiNode> portalNodeRoot;						  // 70
		BSTArray<NiPointer<NiAVObject>> attachAlwaysRenderQueue;  // 78
		BSTArray<NiPointer<NiAVObject>> detachAlwaysRenderQueue;  // 90
		BSTArray<NiPointer<NiNode>> unboundNodes;				  // A8
		std::uint32_t worldID;									  // C0
	};
	static_assert(sizeof(BSPortalGraph) == 0xC8);
}
