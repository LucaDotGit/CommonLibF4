#include "RE/E/ExtraDataList.hpp"

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/C/ComparisonQualifiers.hpp"

namespace RE
{
	auto ExtraDataList::HasExtra(EXTRA_DATA_TYPE a_type) const noexcept -> bool
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);
		return extraList.HasExtra(a_type);
	}

	auto ExtraDataList::GetExtra(EXTRA_DATA_TYPE a_type) const noexcept -> BSExtraData*
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);
		return extraList.GetExtra(a_type);
	}

	auto ExtraDataList::AddExtra(std::unique_ptr<BSExtraData> a_extra) noexcept -> BSExtraData*
	{
		const auto extraLock = BSAutoWriteLock(extraRWLock);
		return extraList.AddExtra(std::move(a_extra));
	}

	auto ExtraDataList::RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept -> std::unique_ptr<BSExtraData>
	{
		const auto extraLock = BSAutoWriteLock(extraRWLock);
		return extraList.RemoveExtra(a_type);
	}

	auto ExtraDataList::CompareList(const ExtraDataList* a_compare, ComparisonQualifier a_qualifier) -> bool
	{
		using FuncType = decltype(&ExtraDataList::CompareList);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ExtraDataList::CompareList);
		return std::invoke(FUNC, this, a_compare, a_qualifier);
	}

	auto ExtraDataList::CompareListForContainer(const ExtraDataList* a_compare) -> bool
	{
		return CompareList(a_compare, ComparisonQualifiers::ContainerQualifier);
	}

	auto ExtraDataList::CompareListForUI(const ExtraDataList* a_compare) -> bool
	{
		return CompareList(a_compare, ComparisonQualifiers::UIQualifier);
	}

	void ExtraDataList::CopyList(const ExtraDataList* a_source)
	{
		using FuncType = decltype(&ExtraDataList::CopyList);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ExtraDataList::CopyList);
		std::invoke(FUNC, this, a_source);
	}

	auto ExtraDataList::CreateInstanceData(TESBoundObject* a_object, bool a_generateName) -> TBO_InstanceData*
	{
		using FuncType = decltype(&ExtraDataList::CreateInstanceData);
		static const auto FUNC = REL::Relocation<FuncType>(ID::ExtraDataList::CreateInstanceData);
		return std::invoke(FUNC, this, a_object, a_generateName);
	}
}
