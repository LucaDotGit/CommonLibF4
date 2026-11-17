#pragma once

#include "REX/W32/CORE.hpp"

namespace REX::W32
{
	auto GetFileVersionInfoA(const char* a_name, std::uint32_t a_handle, std::uint32_t a_dataLength, void* a_data)
		noexcept -> bool;
	auto GetFileVersionInfoSizeA(const char* a_name, std::uint32_t* a_handle) noexcept -> std::uint32_t;
	// std::uint32_t GetFileVersionInfoSizeExA(std::uint32_t a_flags, const char* a_name, std::uint32_t* a_handle)
	// noexcept;
	auto GetFileVersionInfoSizeExW(std::uint32_t a_flags, const wchar_t* a_name, std::uint32_t* a_handle) noexcept
		-> std::uint32_t;
	auto GetFileVersionInfoSizeW(const wchar_t* a_name, std::uint32_t* a_handle) noexcept -> std::uint32_t;
	auto GetFileVersionInfoW(const wchar_t* a_name, std::uint32_t a_handle, std::uint32_t a_dataLength, void* a_data)
		noexcept -> bool;
	auto VerQueryValueA(const void* a_block, const char* a_subBlock, void** a_buffer, std::uint32_t* a_bufferLength)
		noexcept -> bool;
	auto VerQueryValueW(const void* a_block, const wchar_t* a_subBlock, void** a_buffer, std::uint32_t* a_bufferLength)
		noexcept -> bool;
}
