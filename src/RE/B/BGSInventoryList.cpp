#include "RE/B/BGSInventoryList.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	BGSInventoryList::BGSInventoryList(const TESContainer* a_container, ObjectRefHandle a_owner)
	{
		using FuncType = void (BGSInventoryList::*)(const TESContainer*, ObjectRefHandle);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::ctor);
		std::invoke(FUNC, this, a_container, a_owner);
	}

	auto BGSInventoryList::StandardObjectCompareCallbackFn(TESBoundObject* a_lhs, TESBoundObject* a_rhs) -> bool
	{
		return a_lhs == a_rhs;
	}

	void BGSInventoryList::AddItem(
		TESBoundObject* a_item,
		std::uint32_t a_itemCount,
		ExtraDataList* a_itemExtra,
		std::uint16_t a_flags)
	{
		using FuncType = decltype(&BGSInventoryList::AddItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::AddItem);
		std::invoke(FUNC, this, a_item, a_itemCount, a_itemExtra, a_flags);
	}

	void BGSInventoryList::AddStack(
		TESBoundObject* a_item,
		BGSInventoryItem::Stack* a_stack,
		std::uint32_t* a_oldCount,
		std::uint32_t* a_newCount)
	{
		using FuncType = decltype(&BGSInventoryList::AddStack);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::AddStack);
		std::invoke(FUNC, this, a_item, a_stack, a_oldCount, a_newCount);
	}

	void BGSInventoryList::BuildFromContainer(const TESContainer* a_container)
	{
		using FuncType = decltype(&BGSInventoryList::BuildFromContainer);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::BuildFromContainer);
		std::invoke(FUNC, this, a_container);
	}

	void BGSInventoryList::Clear()
	{
		using FuncType = decltype(&BGSInventoryList::Clear);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::Clear);
		std::invoke(FUNC, this);
	}

	auto BGSInventoryList::GetItemCount(const TESBoundObject* a_item) const -> std::uint32_t
	{
		using FuncType = decltype(&BGSInventoryList::GetItemCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::GetItemCount);
		return std::invoke(FUNC, this, a_item);
	}

	auto BGSInventoryList::GetQuestItemCount(const TESBoundObject* a_item) const -> std::uint32_t
	{
		using FuncType = decltype(&BGSInventoryList::GetQuestItemCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::GetQuestItemCount);
		return std::invoke(FUNC, this, a_item);
	}

	void BGSInventoryList::FindAndWriteStackDataForItem(
		TESBoundObject* a_item,
		BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
		BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
		bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*),
		bool a_alwaysContinue)
	{
		using FuncType = decltype(&BGSInventoryList::FindAndWriteStackDataForItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::FindAndWriteStackDataForItem);
		std::invoke(FUNC, this, a_item, a_compareFunc, a_writeFunc, a_objCompFn, a_alwaysContinue);
	}

	auto BGSInventoryList::FindItemIndex(const TESBoundObject* a_item) const -> std::uint32_t
	{
		using FuncType = decltype(&BGSInventoryList::FindItemIndex);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::FindItemIndex);
		return std::invoke(FUNC, this, a_item);
	}

	auto BGSInventoryList::RemoveItem(
		TESBoundObject* a_item,
		std::uint32_t a_stackID,
		std::uint32_t a_itemCount,
		bool a_manualMerge) -> std::uint32_t
	{
		using FuncType = decltype(&BGSInventoryList::RemoveItem);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryList::RemoveItem);
		return std::invoke(FUNC, this, a_item, a_stackID, a_itemCount, a_manualMerge);
	}

	auto BGSInventoryList::ForEachStack(
		const REX::NotNull<
			std::move_only_function<BSContainer::ForEachResult(const BSTSmartPointer<BGSInventoryItem::Stack>&) const>>&
			a_predicate) const -> BSContainer::ForEachResult
	{
		const auto stackLock = BSAutoReadLock(rwLock);

		for (const auto& item : data) {
			for (auto itemStack = item.stackData; itemStack; itemStack = itemStack->nextStack) {
				if (std::invoke(a_predicate.get(), itemStack) == BSContainer::ForEachResult::Stop) {
					return BSContainer::ForEachResult::Stop;
				}
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
