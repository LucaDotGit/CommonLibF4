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
		[[nodiscard]] std::uint32_t GetFileCount() const noexcept;

		BSContainer::ForEachResult ForEachFile(
			const REX::NotNull<std::function<BSContainer::ForEachResult(TESFile*)>>& a_predicate) const;

		// members
		BSTArray<TESFile*> files;	   // 00
		BSTArray<TESFile*> smallFiles; // 18
	};
	static_assert(sizeof(TESFileCollection) == 0x30);
}
