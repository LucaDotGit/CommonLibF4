#include "RE/H/hkContainerDebugAllocator.hpp"

namespace RE
{
	hkContainerDebugAllocator::Allocator& hkContainerDebugAllocator::GetAllocator()
	{
		static const auto ALLOCATOR = REL::Relocation<Allocator*>{ ID::hkContainerDebugAllocator::Allocator };
		return *ALLOCATOR;
	}

	__declspec(allocator) __declspec(restrict) void* hk_container_debug_malloc(std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerDebugAllocator::GetAllocator();
			return allocator.malloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) void* hk_container_debug_calloc(std::size_t a_count, std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerDebugAllocator::GetAllocator();
			return allocator.calloc(a_count, a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void hk_container_debug_free(void* a_ptr, std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerDebugAllocator::GetAllocator();
			allocator.free(a_ptr, a_size);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}
}
