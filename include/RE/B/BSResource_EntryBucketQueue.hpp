#pragma once

#include "RE/B/BSResource_EntryQueue.hpp"

namespace RE::BSResource
{
	template <class T, std::uint32_t N>
	class EntryBucketQueue
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		// members
		std::array<EntryQueue<T>, MAX_SIZE> buckets; // 00
		volatile std::uint32_t step;				 // ??
	};
	static_assert(sizeof(EntryBucketQueue<void, 8>) == 0xC8);
}
