#pragma once

#include "RE/B/BGSInventoryItem.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
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
	class BGSInventoryList
		: public BSTEventSource<BGSInventoryListEvent::Event> // 00
	{
	public:
		BGSInventoryList(const TESContainer* a_container, ObjectRefHandle a_owner);

		GAME_HEAP_REDEFINE_NEW(BGSInventoryList)

		[[nodiscard]] static bool StandardObjectCompareCallbackFn(TESBoundObject* a_lhs, TESBoundObject* a_rhs);

		void FindAndWriteStackDataForItem(
			TESBoundObject* a_object,
			BGSInventoryItem::StackDataCompareFunctor& a_compareFunc,
			BGSInventoryItem::StackDataWriteFunctor& a_writeFunc,
			bool (*a_objCompFn)(TESBoundObject*, TESBoundObject*) = StandardObjectCompareCallbackFn,
			bool a_alwaysContinue = false);
		void BuildFromContainer(const TESContainer* a_container);

		BSContainer::ForEachResult ForEachStack(
			const REX::NotNull<std::function<BSContainer::ForEachResult(const BSTSmartPointer<BGSInventoryItem::Stack>&)>>& a_predicate) const;

		// members
		BSTArray<BGSInventoryItem> data;	  // 58
		REX::Float32 cachedWeight{ 0.0_f32 }; // 70
		ObjectRefHandle owner;				  // 74
		mutable BSReadWriteLock rwLock;		  // 78
	};
	static_assert(sizeof(BGSInventoryList) == 0x80);
}
