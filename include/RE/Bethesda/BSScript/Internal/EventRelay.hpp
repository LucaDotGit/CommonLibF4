#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Object;
}

namespace RE::BSScript::Internal
{
	class EventRelay
		: public BSIntrusiveRefCounted // 00
	{
	public:
		struct TargetList
			: public BSIntrusiveRefCounted // 00
		{
		public:
			// members
			BSTSet<BSTSmartPointer<Object>> targets; // 00
		};
		static_assert(sizeof(TargetList) == 0x38);

		// members
		BSTHashMap<BSFixedString, BSTSmartPointer<TargetList>> events; // 00
	};
	static_assert(sizeof(EventRelay) == 0x38);
}
