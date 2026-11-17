#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class TESFile;

	class TESFileCollection
	{
	public:
		[[nodiscard]]
		auto GetFileCount() const noexcept -> std::uint32_t;

		auto ForEachFile(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(TESFile*) const>>& a_predicate) const
			-> BSContainer::ForEachResult;

		// members
		BSTArray<TESFile*> files;	   // 0x00
		BSTArray<TESFile*> smallFiles; // 0x18
	};

	static_assert(sizeof(TESFileCollection) == 0x30);
}
