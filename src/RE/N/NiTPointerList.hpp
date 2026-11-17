#pragma once

#include "RE/N/NiTList.hpp"
#include "RE/N/NiTPointerAllocator.hpp"

namespace RE
{
	template <class T>
	class NiTPointerList : public NiTPointerListBase<T, NiTPointerAllocator<std::uintptr_t>>
	{
	public:
	};

	static_assert(sizeof(NiTPointerList<void*>) == 0x18);
}
