#include "RE/B/BGSInventoryList.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	BGSInventoryList::BGSInventoryList(const TESContainer* a_container, ObjectRefHandle a_owner)
	{
		using FuncType = void (BGSInventoryList::*)(const TESContainer*, ObjectRefHandle);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryList::ctor };
		std::invoke(FUNC, this, a_container, a_owner);
	}

	bool BGSInventoryList::StandardObjectCompareCallbackFn(TESBoundObject* a_lhs, TESBoundObject* a_rhs)
	{
		return a_lhs == a_rhs;
	}

	void BGSInventoryList::FindAndWriteStackDataForItem(
		TESBoundObject* a_object,
		BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
		BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
		bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*),
		bool a_alwaysContinue)
	{
		using FuncType = decltype(&BGSInventoryList::FindAndWriteStackDataForItem);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryList::FindAndWriteStackDataForItem };
		std::invoke(FUNC, this, a_object, a_compareFunc, a_writeFunc, a_objCompFn, a_alwaysContinue);
	}

	void BGSInventoryList::BuildFromContainer(const TESContainer* a_container)
	{
		using FuncType = decltype(&BGSInventoryList::BuildFromContainer);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryList::BuildFromContainer };
		std::invoke(FUNC, this, a_container);
	}

	BSContainer::ForEachResult BGSInventoryList::ForEachStack(
		const REX::NotNull<std::function<BSContainer::ForEachResult(const BSTSmartPointer<BGSInventoryItem::Stack>&)>>& a_predicate) const
	{
		const auto stackLock = BSAutoReadLock(rwLock);

		for (const auto& item : data) {
			for (auto stack = item.stackData; stack; stack = stack->nextStack) {
				if (std::invoke(*a_predicate, stack) == BSContainer::ForEachResult::kStop) {
					return BSContainer::ForEachResult::kStop;
				}
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
