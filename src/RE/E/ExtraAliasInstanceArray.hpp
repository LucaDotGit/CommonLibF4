#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSReadWriteLock.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSRefAliasInstanceData;

	class __declspec(novtable) ExtraAliasInstanceArray : public BSExtraData // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ExtraAliasInstanceArray;
		inline static constexpr const auto& VTABLE = VTABLE::ExtraAliasInstanceArray;
		inline static constexpr auto EXTRA_TYPE = EXTRA_DATA_TYPE::AliasInstanceArray;

		ExtraAliasInstanceArray() :
			BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAliasInstanceArray() override; // 0x00

		// override (BSExtraData)
		auto CompareImpl(const BSExtraData& a_compare) const -> bool override; // 0x01

		// members
		BSTArray<BGSRefAliasInstanceData> aliasArray; // 0x18
		mutable BSReadWriteLock aliasArrayLock;		  // 0x30
	};

	static_assert(sizeof(ExtraAliasInstanceArray) == 0x38);
}
