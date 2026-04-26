#pragma once

#include "RE/B/BSResource_ID.hpp"
#include "RE/B/BSResource_Stream.hpp"
#include "RE/B/BSTAtomicValue.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSResource
{
	class EntryBase
	{
	public:
		// members
		ID name;							// 00
		BSTAtomicValue<std::uint32_t> ctrl; // 0C
		BSTSmartPointer<Stream> stream;		// 10
	};
	static_assert(sizeof(EntryBase) == 0x18);
}
