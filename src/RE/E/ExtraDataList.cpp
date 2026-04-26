#include "RE/E/ExtraDataList.hpp"

#include "RE/B/BSExtraData.hpp"
#include "RE/C/ComparisonQualifiers.hpp"

namespace RE
{
	bool ExtraDataList::HasExtra(EXTRA_DATA_TYPE a_type) const noexcept
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);
		return extraData.HasExtra(a_type);
	}

	BSExtraData* ExtraDataList::GetExtra(EXTRA_DATA_TYPE a_type) const noexcept
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);
		return extraData.GetExtra(a_type);
	}

	void ExtraDataList::AddExtra(BSExtraData* a_extra) noexcept
	{
		const auto extraLock = BSAutoWriteLock(extraRWLock);
		extraData.AddExtra(a_extra);
	}

	std::unique_ptr<BSExtraData> ExtraDataList::RemoveExtra(EXTRA_DATA_TYPE a_type) noexcept
	{
		const auto extraLock = BSAutoWriteLock(extraRWLock);
		return extraData.RemoveExtra(a_type);
	}

	bool ExtraDataList::CompareList(const ExtraDataList* a_compare, ComparisonQualifier a_qualifier)
	{
		using FuncType = decltype(&ExtraDataList::CompareList);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ExtraDataList::CompareList };
		return std::invoke(FUNC, this, a_compare, a_qualifier);
	}

	bool ExtraDataList::CompareListForContainer(const ExtraDataList* a_compare)
	{
		return CompareList(a_compare, ComparisonQualifiers::ContainerQualifier);
	}

	bool ExtraDataList::CompareListForUI(const ExtraDataList* a_compare)
	{
		return CompareList(a_compare, ComparisonQualifiers::UIQualifier);
	}

	TBO_InstanceData* ExtraDataList::CreateInstanceData(TESBoundObject* a_object, bool a_generateName)
	{
		using FuncType = decltype(&ExtraDataList::CreateInstanceData);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::ExtraDataList::CreateInstanceData };
		return std::invoke(FUNC, this, a_object, a_generateName);
	}
}
