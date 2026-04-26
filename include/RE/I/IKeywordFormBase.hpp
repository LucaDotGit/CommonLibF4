#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class TBO_InstanceData;

	class __declspec(novtable) IKeywordFormBase
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IKeywordFormBase };
		inline static constexpr auto VTABLE{ VTABLE::IKeywordFormBase };

		virtual ~IKeywordFormBase() = default; // 00

		// add
		virtual bool HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_instanceData = nullptr) const = 0;				   // 01
		virtual void CollectAllKeywords(BSScrapArray<const BGSKeyword*>& a_outKeywords, const TBO_InstanceData* a_instanceData) const = 0; // 02
	};
	static_assert(sizeof(IKeywordFormBase) == 0x08);
}
