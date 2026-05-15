#include "RE/H//hkMemoryRouter.hpp"

namespace RE
{
	hkMemoryRouter* hkMemoryRouter::GetInstance()
	{
		static const auto THREAD_LOCAL_INSTANCE = REL::Relocation<std::uint32_t*>{ ID::hkMemoryRouter::ThreadLocalInstance };
		return reinterpret_cast<hkMemoryRouter*>(REX::W32::TlsGetValue(*THREAD_LOCAL_INSTANCE));
	}

	void hkMemoryRouter::SetInstance(hkMemoryRouter* a_router)
	{
		static const auto THREAD_LOCAL_INSTANCE = REL::Relocation<std::uint32_t*>{ ID::hkMemoryRouter::ThreadLocalInstance };
		REX::W32::TlsSetValue(*THREAD_LOCAL_INSTANCE, a_router);
	}

	__declspec(allocator) __declspec(restrict) void* hk_malloc(std::size_t a_size) noexcept
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

	__declspec(allocator) __declspec(restrict) void* hk_temp_malloc(std::size_t a_size) noexcept
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

	__declspec(allocator) __declspec(restrict) void* hk_debug_malloc(std::size_t a_size) noexcept
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

	__declspec(allocator) __declspec(restrict) void* hk_calloc(std::size_t a_count, std::size_t a_size) noexcept
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

	__declspec(allocator) __declspec(restrict) void* hk_temp_calloc(std::size_t a_count, std::size_t a_size) noexcept
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

	__declspec(allocator) __declspec(restrict) void* hk_debug_calloc(std::size_t a_count, std::size_t a_size) noexcept
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
