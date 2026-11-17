#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::GameScript::Internal
{
	class MagicEffectApplyFilter;

	class MagicEffectApplyFilterSet : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSTArray<MagicEffectApplyFilter> filters; // 0x08
	};

	static_assert(sizeof(MagicEffectApplyFilterSet) == 0x20);
}
