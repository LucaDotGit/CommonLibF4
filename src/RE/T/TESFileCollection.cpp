#include "RE/T/TESFileCollection.hpp"

#include "RE/B/BSContainer_ForEachResult.hpp"

namespace RE
{
	auto TESFileCollection::GetFileCount() const noexcept -> std::uint32_t
	{
		return files.size() + smallFiles.size();
	}

	auto TESFileCollection::ForEachFile(
		const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESFile*) const>>& a_predicate) const
		-> BSContainer::ForEachResult
	{
		for (auto* file : files) {
			if (std::invoke(a_predicate.get(), file) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		for (auto* file : smallFiles) {
			if (std::invoke(a_predicate.get(), file) == BSContainer::ForEachResult::Stop) {
				return BSContainer::ForEachResult::Stop;
			}
		}

		return BSContainer::ForEachResult::Continue;
	}
}
