#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class TESContainer;
}

namespace RE::BGSInventoryListEvent
{
	class Event;
}

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class BGSInventoryList : public BSTEventSource<BGSInventoryListEvent::Event> // 0x00
	{
	public:
		BGSInventoryList(const TESContainer* a_container, ObjectRefHandle a_ownerHandle);

		GAME_HEAP_REDEFINE_NEW(BGSInventoryList);

		[[nodiscard]]
		static auto StandardObjectCompareCallbackFn(TESBoundObject* a_lhs, TESBoundObject* a_rhs) -> bool;

		void AddItem(
			TESBoundObject* a_item,
			std::uint32_t a_itemCount = 1,
			ExtraDataList* a_itemExtra = nullptr,
			std::uint16_t a_flags = 0);
		void AddStack(
			TESBoundObject* a_item,
			BGSInventoryItem::Stack* a_stack,
			std::uint32_t* a_oldCount = nullptr,
			std::uint32_t* a_newCount = nullptr);
		void BuildFromContainer(const TESContainer* a_container);
		void Clear();
		[[nodiscard]]
		auto GetItemCount(const TESBoundObject* a_item) const -> std::uint32_t;
		[[nodiscard]]
		auto GetQuestItemCount(const TESBoundObject* a_item) const -> std::uint32_t;
		void FindAndWriteStackDataForItem(
			TESBoundObject* a_item,
			BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
			BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
			bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = StandardObjectCompareCallbackFn,
			bool a_alwaysContinue = false);
		[[nodiscard]]
		auto FindItemIndex(const TESBoundObject* a_item) const -> std::uint32_t;
		auto RemoveItem(
			TESBoundObject* a_item,
			std::uint32_t a_stackID = 0,
			std::uint32_t a_itemCount = 1,
			bool a_manualMerge = false) -> std::uint32_t;

		auto ForEachStack(
			const REX::NotNull<std::move_only_function<
				BSContainer::ForEachResult(const BSTSmartPointer<BGSInventoryItem::Stack>&) const>>& a_predicate) const
			-> BSContainer::ForEachResult;

		// members
		BSTArray<BGSInventoryItem> data;						   // 0x58
		REX::Float32 cachedWeight{static_cast<REX::Float32>(0.0)}; // 0x70
		ObjectRefHandle owner;									   // 0x74
		mutable BSReadWriteLock rwLock;							   // 0x78
	};

	static_assert(sizeof(BGSInventoryList) == 0x80);
}
