#include "RE/B/BSResource_AsyncStream.hpp"

namespace RE::BSResource
{
	AsyncStream::AsyncStream()
	{
		REL::EmplaceVtable(this);
	}

	AsyncStream::AsyncStream(std::uint32_t a_totalSize, bool writable)
		: StreamBase(a_totalSize, writable)
	{
		REL::EmplaceVtable(this);
	}
}
