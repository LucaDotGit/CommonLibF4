#include "REL/Memory.hpp"

#include "REX/Error.hpp"
#include "REX/W32/KERNEL32.hpp"

namespace REL
{
	auto Write(void* a_target, const void* a_source, std::size_t a_size) noexcept -> std::size_t
	{
		if (!a_target || !a_source || a_size == 0) {
			return 0;
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, reinterpret_cast<std::byte*>(a_target));
		return a_size;
	}

	auto Write(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept -> std::size_t
	{
		if (!a_target || !a_source || a_size == 0) {
			return 0;
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, std::bit_cast<std::byte*>(a_target));
		return a_size;
	}

	auto WriteFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept -> std::size_t
	{
		if (!a_target || a_size == 0) {
			return 0;
		}

		std::fill_n(reinterpret_cast<std::byte*>(a_target), a_size, static_cast<std::byte>(a_value));
		return a_size;
	}

	auto WriteFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept -> std::size_t
	{
		if (!a_target || a_size == 0) {
			return 0;
		}

		std::fill_n(std::bit_cast<std::byte*>(a_target), a_size, static_cast<std::byte>(a_value));
		return a_size;
	}

	auto WriteSafe(void* a_target, const void* a_source, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		if (!a_target || !a_source || a_size == 0) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS));
		}

		auto oldProtect = static_cast<std::uint32_t>(0);
		if (!REX::W32::VirtualProtect(a_target, a_size, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(oldProtect)))
			[[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, reinterpret_cast<std::byte*>(a_target));

		if (!REX::W32::VirtualProtect(a_target, a_size, oldProtect, std::addressof(oldProtect))) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		if (!REX::W32::FlushInstructionCache(REX::W32::GetCurrentProcess(), a_target, a_size)) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return a_size;
	}

	auto WriteSafe(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafe(std::bit_cast<void*>(a_target), a_source, a_size);
	}

	auto WriteSafeFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		if (!a_target || a_size == 0) [[unlikely]] {
			return std::unexpected(REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS));
		}

		auto oldProtect = static_cast<std::uint32_t>(0);
		if (!REX::W32::VirtualProtect(a_target, a_size, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(oldProtect)))
			[[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		std::fill_n(reinterpret_cast<std::byte*>(a_target), a_size, static_cast<std::byte>(a_value));

		if (!REX::W32::VirtualProtect(a_target, a_size, oldProtect, std::addressof(oldProtect))) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		if (!REX::W32::FlushInstructionCache(REX::W32::GetCurrentProcess(), a_target, a_size)) [[unlikely]] {
			return std::unexpected(REX::GetCurrentSystemError());
		}

		return a_size;
	}

	auto WriteSafeFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept
		-> std::expected<std::size_t, REX::SystemError>
	{
		return WriteSafeFill(std::bit_cast<void*>(a_target), a_value, a_size);
	}

	void WriteZeros(void* a_ptr, std::size_t a_size) noexcept
	{
		WriteFill(a_ptr, 0, a_size);
	}

	void WriteZeros(std::uintptr_t a_ptr, std::size_t a_size) noexcept
	{
		WriteFill(a_ptr, 0, a_size);
	}

	__declspec(allocator) __declspec(restrict) auto AlignedAllocate(std::size_t a_size, std::align_val_t a_alignment)
		noexcept -> void*
	{
#if (_WIN32 == 1)
		return ::_aligned_malloc(a_size, static_cast<std::size_t>(a_alignment));
#else
		return std::aligned_alloc(a_size, static_cast<std::size_t>(a_alignment));
#endif
	}

	__declspec(noalias) void AlignedFree(void* a_ptr) noexcept
	{
#if (_WIN32 == 1)
		::_aligned_free(a_ptr);
#else
		std::free(a_ptr);
#endif
	}
}
