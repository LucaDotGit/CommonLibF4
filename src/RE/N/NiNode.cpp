#include "RE/N/NiNode.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	NiNode::NiNode() :
		NiNode(0)
	{
	}

	NiNode::NiNode(std::uint32_t a_numChildren)
	{
		auto& runtimeData = GetRuntimeData();
		runtimeData.children = NiTObjectArray<NiPointer<NiAVObject>>(static_cast<std::uint16_t>(a_numChildren));
		runtimeData.dirtyState = 0;
		runtimeData.meshLODFadeAmount = static_cast<REX::Float32>(0.0);

		REL::EmplaceVtable(this);
		REL::EmplaceVtable(std::addressof(runtimeData.children), VTABLE::NiTObjectArray_NiPointer_NiAVObject__);
	}

	NiNode::~NiNode() = default;

	auto NiNode::GetRuntimeData() noexcept -> NiNode::RuntimeData&
	{
		return REL::GetMemberAt<RuntimeData>(Offset::NiNode::RuntimeData, this);
	}

	auto NiNode::GetRuntimeData() const noexcept -> const NiNode::RuntimeData&
	{
		return REL::GetMemberAt<const RuntimeData>(Offset::NiNode::RuntimeData, this);
	}

	auto NiNode::GetChildCount() const -> std::uint32_t
	{
		return static_cast<std::uint32_t>(GetRuntimeData().children.size());
	}

	auto NiNode::GetChildAt(std::uint32_t a_index) const -> NiPointer<NiAVObject>
	{
		if (a_index >= GetRuntimeData().children.size()) {
			return nullptr;
		}

		return GetRuntimeData().children[static_cast<std::uint16_t>(a_index)];
	}

	auto NiNode::SetChildAt(std::uint32_t a_index, NiPointer<NiAVObject> a_child) -> bool
	{
		if (a_index >= GetRuntimeData().children.size()) {
			return false;
		}

		GetRuntimeData().children[static_cast<std::uint16_t>(a_index)] = std::move(a_child);
		return true;
	}

	auto NiNode::ForEachChild(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(const NiPointer<NiAVObject>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		for (const auto& child : GetRuntimeData().children) {
			if (std::invoke(a_predicate.get(), child) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
