#pragma once

#include "RE/NetImmerse/NiTDefaultAllocator.hpp"
#include "RE/NetImmerse/NiTPointerListBase.hpp"

namespace RE
{
	template <class T>
	class NiTList
		: public NiTPointerListBase<NiTDefaultAllocator<T>, T> // 00
	{
	public:
	};
}
