#include "RE/B/BGSInventoryItem.hpp"

namespace RE
{
	auto BGSInventoryItem::IsEquipped(std::uint32_t a_stackID) const -> bool
	{
		using FuncType = decltype(&BGSInventoryItem::IsEquipped);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::IsEquipped);
		return std::invoke(FUNC, this, a_stackID);
	}

	auto BGSInventoryItem::FindAndWriteStackData(
		StackDataCompareFunctor& a_compareFunc,
		StackDataWriteFunctor& a_writeFunc,
		bool a_manualMerge,
		ObjectRefHandle a_owner) -> bool
	{
		using FuncType = decltype(&BGSInventoryItem::FindAndWriteStackData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::FindAndWriteStackData);
		return std::invoke(FUNC, this, a_compareFunc, a_writeFunc, a_manualMerge, a_owner);
	}

	auto BGSInventoryItem::GetCount() const noexcept -> std::uint32_t
	{
		auto count = static_cast<std::uint32_t>(0);
		for (auto* stackIt = stackData.get(); stackIt; stackIt = stackIt->nextStack.get()) {
			count += stackIt->count;
		}

		return count;
	}

	auto BGSInventoryItem::GetStackByID(std::uint32_t a_stackID) const -> BGSInventoryItem::Stack*
	{
		auto* stackIt = stackData.get();
		while (stackIt && a_stackID--) {
			stackIt = stackIt->nextStack.get();
		}

		return stackIt;
	}

	auto BGSInventoryItem::GetDisplayFullName(std::uint32_t a_stackID) const -> const char*
	{
		using FuncType = const char* (BGSInventoryItem::*)(std::uint32_t) const;
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetDisplayFullName01);
		return std::invoke(FUNC, this, a_stackID);
	}

	auto BGSInventoryItem::GetDisplayFullName(const ExtraDataList* a_extra) const -> const char*
	{
		using FuncType = const char* (BGSInventoryItem::*)(const ExtraDataList*) const;
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetDisplayFullName02);
		return std::invoke(FUNC, this, a_extra);
	}

	auto BGSInventoryItem::GetInstanceData(std::uint32_t a_stackID) const -> TBO_InstanceData*
	{
		using FuncType = decltype(&BGSInventoryItem::GetInstanceData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetInstanceData);
		return std::invoke(FUNC, this, a_stackID);
	}

	auto BGSInventoryItem::GetInventoryValue(std::uint32_t a_stackID, bool a_scale) const -> std::int32_t
	{
		using FuncType = decltype(&BGSInventoryItem::GetInventoryValue);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetInventoryValue);
		return std::invoke(FUNC, this, a_stackID, a_scale);
	}

	auto BGSInventoryItem::GetExtraDataAt(std::uint32_t a_index) const -> ExtraDataList*
	{
		using FuncType = decltype(&BGSInventoryItem::GetExtraDataAt);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetExtraDataAt);
		return std::invoke(FUNC, this, a_index);
	}

	auto BGSInventoryItem::GetStackCount() const -> std::uint64_t
	{
		using FuncType = decltype(&BGSInventoryItem::GetStackCount);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetStackCount);
		return std::invoke(FUNC, this);
	}

	auto BGSInventoryItem::GetTotalWeight() const -> REX::Float32
	{
		using FuncType = decltype(&BGSInventoryItem::GetTotalWeight);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::GetTotalWeight);
		return std::invoke(FUNC, this);
	}

	auto BGSInventoryItem::IsQuestObject(std::int32_t a_stackIterations) const -> bool
	{
		using FuncType = decltype(&BGSInventoryItem::IsQuestObject);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::IsQuestObject);
		return std::invoke(FUNC, this, a_stackIterations);
	}

	void BGSInventoryItem::MergeStacks()
	{
		using FuncType = decltype(&BGSInventoryItem::MergeStacks);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BGSInventoryItem::MergeStacks);
		std::invoke(FUNC, this);
	}
}
