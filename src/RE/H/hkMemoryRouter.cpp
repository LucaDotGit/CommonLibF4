#include "RE/H/hkMemoryRouter.hpp"

namespace RE
{
	auto hkMemoryRouter::GetThreadLocalIndex() noexcept -> std::uint32_t
	{
		static const auto THREAD_LOCAL_INDEX = REL::Relocation<std::uint32_t*>(ID::hkMemoryRouter::ThreadLocalIndex);
		return *THREAD_LOCAL_INDEX;
	}

	auto hkMemoryRouter::GetInstance() noexcept -> hkMemoryRouter*
	{
		return static_cast<hkMemoryRouter*>(REX::W32::TlsGetValue(GetThreadLocalIndex()));
	}

	void hkMemoryRouter::SetInstance(hkMemoryRouter* a_router) noexcept
	{
		REX::W32::TlsSetValue(GetThreadLocalIndex(), a_router);
	}

	__declspec(allocator) __declspec(restrict) auto hk_malloc(std::size_t a_size) noexcept -> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->heap;
		if (!allocator) {
			return nullptr;
		}

		return allocator->malloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) auto hk_temp_malloc(std::size_t a_size) noexcept -> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->temp;
		if (!allocator) {
			return nullptr;
		}

		return allocator->malloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) auto hk_debug_malloc(std::size_t a_size) noexcept -> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->debug;
		if (!allocator) {
			return nullptr;
		}

		return allocator->malloc(a_size);
	}

	__declspec(allocator) __declspec(restrict) auto hk_calloc(std::size_t a_count, std::size_t a_size) noexcept -> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->heap;
		if (!allocator) {
			return nullptr;
		}

		return allocator->calloc(a_count, a_size);
	}

	__declspec(allocator) __declspec(restrict) auto hk_temp_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->temp;
		if (!allocator) {
			return nullptr;
		}

		return allocator->calloc(a_count, a_size);
	}

	__declspec(allocator) __declspec(restrict) auto hk_debug_calloc(std::size_t a_count, std::size_t a_size) noexcept
		-> void*
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) {
			return nullptr;
		}

		auto* allocator = router->debug;
		if (!allocator) {
			return nullptr;
		}

		return allocator->calloc(a_count, a_size);
	}

	__declspec(noalias) void hk_free(void* a_ptr, std::size_t a_size) noexcept
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto* allocator = router->heap;
		if (!allocator) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		allocator->free(a_ptr, a_size);
	}

	__declspec(noalias) void hk_temp_free(void* a_ptr, std::size_t a_size) noexcept
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto* allocator = router->temp;
		if (!allocator) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		allocator->free(a_ptr, a_size);
	}

	__declspec(noalias) void hk_debug_free(void* a_ptr, std::size_t a_size) noexcept
	{
		auto* router = hkMemoryRouter::GetInstance();
		if (!router) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		auto* allocator = router->debug;
		if (!allocator) [[unlikely]] {
			REX::Assert(false);
			return;
		}

		allocator->free(a_ptr, a_size);
	}
}
