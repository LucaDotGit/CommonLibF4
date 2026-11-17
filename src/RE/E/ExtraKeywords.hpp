#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE
{
	class __declspec(novtable) ExtraKeywords : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraKeywords;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraKeywords;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::Keywords;

		ExtraKeywords() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraKeywords() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		auto ForEachKeyword(
			const REX::NotNull<std::move_only_function<BSContainer::ForEachResult(BGSKeyword*) const>>& a_predicate)
			const -> BSContainer::ForEachResult;

		BSTArray<BGSKeyword*> extraKeywords; // 0x18
		mutable BSReadWriteLock extraRWLock; // 0x28
	};

	static_assert(sizeof(ExtraKeywords) == 0x38);
}
