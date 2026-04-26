#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) ExtraKeywords
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraKeywords };
		inline static constexpr auto VTABLE{ VTABLE::ExtraKeywords };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kKeywords };

		ExtraKeywords()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraKeywords() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		BSContainer::ForEachResult ForEachKeyword(
			const REX::NotNull<std::function<BSContainer::ForEachResult(BGSKeyword*)>>& a_predicate) const;

		BSTArray<BGSKeyword*> extraKeywords; // 18
		mutable BSReadWriteLock extraRWLock; // 28
	};
	static_assert(sizeof(ExtraKeywords) == 0x38);
}
