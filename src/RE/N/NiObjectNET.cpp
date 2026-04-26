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
}
