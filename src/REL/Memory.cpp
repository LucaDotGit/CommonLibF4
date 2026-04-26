#include "REL/Memory.hpp"

#include "REX/W32/KERNEL32.hpp"

namespace REL
{
	void Write(void* a_target, const void* a_source, std::size_t a_size) noexcept
	{
		if (a_size == 0) {
			return;
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, reinterpret_cast<std::byte*>(a_target));
	}

	void Write(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept
	{
		if (a_size == 0) {
			return;
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, std::bit_cast<std::byte*>(a_target));
	}

	REX::SystemError WriteSafe(void* a_target, const void* a_source, std::size_t a_size) noexcept
	{
		if (a_size == 0) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto oldProtect = 0ui32;
		if (!REX::W32::VirtualProtect(a_target, a_size, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(oldProtect))) {
			return REX::GetCurrentSystemError();
		}

		std::copy_n(reinterpret_cast<const std::byte*>(a_source), a_size, reinterpret_cast<std::byte*>(a_target));

		if (!REX::W32::VirtualProtect(a_target, a_size, oldProtect, std::addressof(oldProtect))) {
			return REX::GetCurrentSystemError();
		}

		if (!REX::W32::FlushInstructionCache(REX::W32::GetCurrentProcess(), a_target, a_size)) {
			return REX::GetCurrentSystemError();
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	REX::SystemError WriteSafe(std::uintptr_t a_target, const void* a_source, std::size_t a_size) noexcept
	{
		return WriteSafe(std::bit_cast<void*>(a_target), a_source, a_size);
	}

	REX::SystemError WriteSafeFill(void* a_target, std::uint8_t a_value, std::size_t a_size) noexcept
	{
		if (a_size == 0) {
			return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
		}

		auto oldProtect = 0ui32;
		if (!REX::W32::VirtualProtect(a_target, a_size, REX::W32::PAGE_EXECUTE_READWRITE, std::addressof(oldProtect))) {
			return REX::GetCurrentSystemError();
		}

		std::fill_n(reinterpret_cast<std::byte*>(a_target), a_size, static_cast<std::byte>(a_value));

		if (!REX::W32::VirtualProtect(a_target, a_size, oldProtect, std::addressof(oldProtect))) {
			return REX::GetCurrentSystemError();
		}

		if (!REX::W32::FlushInstructionCache(REX::W32::GetCurrentProcess(), a_target, a_size)) {
			return REX::GetCurrentSystemError();
		}

		return REX::CreateSystemError(REX::ERROR_NUMBER_SUCCESS);
	}

	REX::SystemError WriteSafeFill(std::uintptr_t a_target, std::uint8_t a_value, std::size_t a_size) noexcept
	{
		return WriteSafeFill(std::bit_cast<void*>(a_target), a_value, a_size);
	}
}
