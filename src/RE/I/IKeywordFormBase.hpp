#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class TBO_InstanceData;

	class __declspec(novtable) IKeywordFormBase
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IKeywordFormBase;
		inline static constexpr const auto& VTABLE = VTABLE::IKeywordFormBase;

		virtual ~IKeywordFormBase() = default; // 0x00

		// add
		virtual auto HasKeyword(const BGSKeyword* a_keyword, const TBO_InstanceData* a_instanceData = nullptr) const
			-> bool = 0; // 0x01
		virtual void CollectAllKeywords(
			BSScrapArray<const BGSKeyword*>& a_outKeywords,
			const TBO_InstanceData* a_instanceData) const = 0; // 0x02

		GAME_HEAP_REDEFINE_NEW(IKeywordFormBase);
	};

	static_assert(sizeof(IKeywordFormBase) == 0x08);
}
