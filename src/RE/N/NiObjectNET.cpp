#include "RE/N/NiObjectNET.hpp"

#include "RE/B/BSSpinLock.hpp"

namespace RE
{
	NiObjectNET::NiObjectNET()
	{
		REL::EmplaceVtable(this);
	}

	NiObjectNET::~NiObjectNET()
	{
		if (!extra) {
			return;
		}

		const auto extraLock = BSAutoWriteLock(extra->lock);

		for (auto& extraData : extra->dataArray) {
			extraData->DecRefCount();
		}

		delete extra;
		extra = nullptr;
	}

	bool NiObjectNET::AddExtraData(NiPointer<NiExtraData> a_extraData) const
	{
		if (!extra || !a_extraData) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extra->lock);

		for (auto& extraData : extra->dataArray) {
			if (extraData->name == a_extraData->name) {
				return false;
			}
		}

		extra->dataArray.push_back(std::move(a_extraData));
		return true;
	}

	NiPointer<NiExtraData> NiObjectNET::GetExtraData(const BSFixedString& a_key) const noexcept
	{
		if (!extra) {
			return nullptr;
		}

		const auto extraLock = BSAutoReadLock(extra->lock);

		for (auto& extraData : extra->dataArray) {
			if (extraData->name == a_key) {
				return extraData;
			}
		}

		return nullptr;
	}

	bool NiObjectNET::HasExtraData(const BSFixedString& a_key) const noexcept
	{
		return GetExtraData(a_key) != nullptr;
	}

	bool NiObjectNET::RemoveExtraData(const BSFixedString& a_key) const
	{
		if (!extra) {
			return false;
		}

		const auto extraLock = BSAutoWriteLock(extra->lock);

		for (auto& extraData : extra->dataArray) {
			if (extraData->name == a_key) {
				extra->dataArray.erase(std::addressof(extraData));
				return true;
			}
		}

		return false;
	}
}
