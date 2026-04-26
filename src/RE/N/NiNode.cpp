#include "RE/N/NiNode.hpp"

namespace RE
{
	NiNode::NiNode()
		: NiNode(0)
	{
	}

	NiNode::NiNode(std::uint32_t a_numChildren)
		: children(static_cast<decltype(children)::size_type>(a_numChildren))
	{
		REL::EmplaceVtable(this);
		REL::EmplaceVtable(std::addressof(children), VTABLE::NiTObjectArray_NiPointer_NiAVObject__);
	}

	NiNode::RuntimeData& NiNode::GetRuntimeData() noexcept
	{
		return REL::GetMemberAt<RuntimeData>(Offset::NiNode::RuntimeData, this);
	}

	const NiNode::RuntimeData& NiNode::GetRuntimeData() const noexcept
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::NiNode::RuntimeData, this);
	}
}
