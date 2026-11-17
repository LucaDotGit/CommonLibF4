#include "RE/H/hkContainerTempAllocator.hpp"

namespace RE
{
	auto hkContainerTempAllocator::GetAllocator() noexcept -> hkContainerTempAllocator::Allocator&
	{
		static const auto ALLOCATOR = REL::Relocation<Allocator*>(ID::hkContainerTempAllocator::Allocator);
		return *ALLOCATOR;
	}

	__declspec(allocator) __declspec(restrict) auto hk_container_temp_malloc(std::size_t a_size) noexcept -> void*
	{
		try {
			auto& allocator = hkContainerTempAllocator::GetAllocator();
			return allocator.malloc(a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(allocator) __declspec(restrict) auto hk_container_temp_calloc(std::size_t a_count, std::size_t a_size)
		noexcept -> void*
	{
		try {
			auto& allocator = hkContainerTempAllocator::GetAllocator();
			return allocator.calloc(a_count, a_size);
		}
		catch (...) {
			return nullptr;
		}
	}

	__declspec(noalias) void hk_container_temp_free(void* a_ptr, std::size_t a_size) noexcept
	{
		try {
			auto& allocator = hkContainerTempAllocator::GetAllocator();
			allocator.free(a_ptr, a_size);
		}
		catch (...) {
			REX::Fail("Failed to free memory."sv);
		}
	}
}
