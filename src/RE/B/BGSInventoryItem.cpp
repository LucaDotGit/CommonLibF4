#include "RE/B/BGSInventoryItem.hpp"

namespace RE
{
	bool BGSInventoryItem::IsEquipped(std::uint32_t a_stackID) const
	{
		using FuncType = decltype(&BGSInventoryItem::IsEquipped);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::IsEquipped };
		return std::invoke(FUNC, this, a_stackID);
	}

	bool BGSInventoryItem::FindAndWriteStackData(StackDataCompareFunctor& a_compareFunc, StackDataWriteFunctor& a_writeFunc, bool a_manualMerge, ObjectRefHandle a_owner)
	{
		using FuncType = decltype(&BGSInventoryItem::FindAndWriteStackData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::FindAndWriteStackData };
		return std::invoke(FUNC, this, a_compareFunc, a_writeFunc, a_manualMerge, a_owner);
	}

	std::uint32_t BGSInventoryItem::GetCount() const noexcept
	{
		auto count = 0ui32;
		for (auto* stackIt = stackData.get(); stackIt; stackIt = stackIt->nextStack.get()) {
			count += stackIt->count;
		}

		return count;
	}

	BGSInventoryItem::Stack* BGSInventoryItem::GetStackByID(std::uint32_t a_stackID) const
	{
		auto* stackIt = stackData.get();
		while (stackIt && a_stackID--) {
			stackIt = stackIt->nextStack.get();
		}

		return stackIt;
	}

	const char* BGSInventoryItem::GetDisplayFullName(std::uint32_t a_stackID) const
	{
		using FuncType = const char* (BGSInventoryItem::*)(std::uint32_t) const;
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetDisplayFullName01 };
		return std::invoke(FUNC, this, a_stackID);
	}

	const char* BGSInventoryItem::GetDisplayFullName(const ExtraDataList* a_extra) const
	{
		using FuncType = const char* (BGSInventoryItem::*)(const ExtraDataList*) const;
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetDisplayFullName02 };
		return std::invoke(FUNC, this, a_extra);
	}

	TBO_InstanceData* BGSInventoryItem::GetInstanceData(std::uint32_t a_stackID) const
	{
		using FuncType = decltype(&BGSInventoryItem::GetInstanceData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetInstanceData };
		return std::invoke(FUNC, this, a_stackID);
	}

	std::int32_t BGSInventoryItem::GetInventoryValue(std::uint32_t a_stackID, bool a_scale) const
	{
		using FuncType = decltype(&BGSInventoryItem::GetInventoryValue);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetInventoryValue };
		return std::invoke(FUNC, this, a_stackID, a_scale);
	}

	ExtraDataList* BGSInventoryItem::GetExtraDataAt(std::uint32_t a_index) const
	{
		using FuncType = decltype(&BGSInventoryItem::GetExtraDataAt);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetExtraDataAt };
		return std::invoke(FUNC, this, a_index);
	}

	std::uint64_t BGSInventoryItem::GetStackCount() const
	{
		using FuncType = decltype(&BGSInventoryItem::GetStackCount);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetStackCount };
		return std::invoke(FUNC, this);
	}

	REX::Float32 BGSInventoryItem::GetTotalWeight() const
	{
		using FuncType = decltype(&BGSInventoryItem::GetTotalWeight);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::GetTotalWeight };
		return std::invoke(FUNC, this);
	}

	bool BGSInventoryItem::IsQuestObject(std::int32_t a_stackIterations) const
	{
		using FuncType = decltype(&BGSInventoryItem::IsQuestObject);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::IsQuestObject };
		return std::invoke(FUNC, this, a_stackIterations);
	}

	void BGSInventoryItem::MergeStacks()
	{
		using FuncType = decltype(&BGSInventoryItem::MergeStacks);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSInventoryItem::MergeStacks };
		FUNC(this);
	}
}
