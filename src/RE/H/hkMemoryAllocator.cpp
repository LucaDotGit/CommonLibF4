#include "RE/H/hkMemoryAllocator.hpp"

namespace RE
{
	__declspec(allocator) __declspec(restrict) auto hkMemoryAllocator::malloc(std::size_t a_size) noexcept -> void*
	{
		try {
			return BlockAlloc(static_cast<std::int32_t>(a_size));
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto hkMemoryAllocator::calloc(std::size_t a_count, std::size_t a_size)
		noexcept -> void*
	{
		try {
			auto* mem = malloc(a_count * a_size);
			if (!mem) {
				return nullptr;
			}

			REL::WriteZeros(mem, a_count * a_size);
			return mem;
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void hkMemoryAllocator::free(void* a_ptr, std::size_t a_size) noexcept
	{
		if (!a_ptr) {
			return;
		}

		try {
			BlockFree(a_ptr, static_cast<std::int32_t>(a_size));
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}
}
