#pragma once

#include "RE/B/BSPointerAllocator.hpp"

namespace RE
{
	template <class T>
	class NiTPointerAllocator
		: public BSPointerAllocator // 00
	{
	public:
	};
	static_assert(std::is_empty_v<NiTPointerAllocator<void*>>);
}
