#pragma once

#include "RE/B/BSNonReentrantSpinLock.hpp"

namespace RE::BSResource
{
	template <class T>
	class EntryQueue
	{
	public:
		// members
		mutable BSNonReentrantSpinLock lock; // 0x00
		T* head;							 // 0x08
		T** tail;							 // 0x10
	};

	static_assert(sizeof(EntryQueue<std::any>) == 0x18);
}
