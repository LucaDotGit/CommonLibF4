#include "RE/Bethesda/TESObjectREFRs.hpp"

#include "RE/NetImmerse/NiAVObject.hpp"

namespace RE
{
	BIPOBJECT::~BIPOBJECT()
	{
		Dtor();
		stl::memzero(this);
	}

	BSContainer::ForEachResult BGSInventoryList::ForEachStack(std::function<BSContainer::ForEachResult(BGSInventoryItem::Stack&)> a_callback) const
	{
		const auto lock = BSAutoReadLock{ rwLock };

		for (auto& elem : data) {
			for (auto* stack = elem.stackData.get(); stack; stack = stack->nextStack.get()) {
				if (a_callback(*stack) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
