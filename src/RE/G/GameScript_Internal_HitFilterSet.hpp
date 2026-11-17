#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE::GameScript::Internal
{
	class HitFilter;

	class HitFilterSet : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSTArray<HitFilter> filters; // 0x08
	};

	static_assert(sizeof(HitFilterSet) == 0x20);
}
