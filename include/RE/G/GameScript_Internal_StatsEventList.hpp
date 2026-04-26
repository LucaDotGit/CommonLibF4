#pragma once

#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::GameScript::Internal
{
	class StatsEventList
		: public BSIntrusiveRefCounted // 00
	{
	public:
		// members
		BSTArray<BSTSmartPointer<BSScript::Object>> objects; // 08
	};
	static_assert(sizeof(StatsEventList) == 0x20);
}
