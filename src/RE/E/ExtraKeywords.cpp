#include "RE/E/ExtraKeywords.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	BSContainer::ForEachResult ExtraKeywords::ForEachKeyword(
		const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate) const
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);

		for (auto* keyword : extraKeywords) {
			if (keyword && std::invoke(*a_predicate, keyword) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
