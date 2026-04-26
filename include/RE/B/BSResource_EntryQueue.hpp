#pragma once

#include "RE/B/BSSpinLock.hpp"

namespace RE::BSResource
{
	template <class T>
	class EntryQueue
	{
	public:
		// members
		mutable BSNonReentrantSpinLock lock; // 00
		T* head;							 // 08
		T** tail;							 // 10
	};
	static_assert(sizeof(EntryQueue<std::any>) == 0x18);
}
