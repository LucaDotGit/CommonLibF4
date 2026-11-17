#include "RE/E/ExtraKeywords.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSReadWriteLock.hpp"

namespace RE
{
	auto ExtraKeywords::ForEachKeyword(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		const auto extraLock = BSAutoReadLock(extraRWLock);

		for (auto* keyword : extraKeywords) {
			if (std::invoke(a_predicate.get(), keyword) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
