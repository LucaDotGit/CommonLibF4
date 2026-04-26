#pragma once

#include "RE/B/BSExtraData.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BGSRefAliasInstanceData;

	class __declspec(novtable) ExtraAliasInstanceArray
		: public BSExtraData // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ExtraAliasInstanceArray };
		inline static constexpr auto VTABLE{ VTABLE::ExtraAliasInstanceArray };
		inline static constexpr auto EXTRA_TYPE{ EXTRA_DATA_TYPE::kAliasInstanceArray };

		ExtraAliasInstanceArray()
			: BSExtraData(EXTRA_TYPE)
		{
			REL::EmplaceVtable(this);
		}

		~ExtraAliasInstanceArray() override; // 00

		// override (BSExtraData)
		bool CompareImpl(const BSExtraData& a_compare) const override; // 01

		// members
		BSTArray<BGSRefAliasInstanceData> aliasArray; // 18
		mutable BSReadWriteLock aliasArrayLock;		  // 30
	};
	static_assert(sizeof(ExtraAliasInstanceArray) == 0x38);
}
