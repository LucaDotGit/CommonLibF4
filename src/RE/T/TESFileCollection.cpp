#include "RE/T/TESFileCollection.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	std::uint32_t TESFileCollection::GetFileCount() const noexcept
	{
		return files.size() + smallFiles.size();
	}

	BSContainer::ForEachResult TESFileCollection::ForEachFile(
		const REX::NotNull<std::function<BSContainer::ForEachResult(TESFile*)>>& a_predicate) const
	{
		for (auto* file : files) {
			if (std::invoke(*a_predicate, file) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		for (auto* file : smallFiles) {
			if (std::invoke(*a_predicate, file) == BSContainer::ForEachResult::kStop) {
				return BSContainer::ForEachResult::kStop;
			}
		}

		return BSContainer::ForEachResult::kContinue;
	}
}
