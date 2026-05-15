#include "REX/Hash.hpp"

namespace REX
{
	template std::size_t Hash(const bool&) noexcept;
	template std::size_t Hash(const char&) noexcept;
	template std::size_t Hash(const wchar_t&) noexcept;
	template std::size_t Hash(const char8_t&) noexcept;
	template std::size_t Hash(const char16_t&) noexcept;
	template std::size_t Hash(const char32_t&) noexcept;
	template std::size_t Hash(const std::int8_t&) noexcept;
	template std::size_t Hash(const std::uint8_t&) noexcept;
	template std::size_t Hash(const std::int16_t&) noexcept;
	template std::size_t Hash(const std::uint16_t&) noexcept;
	template std::size_t Hash(const std::int32_t&) noexcept;
	template std::size_t Hash(const std::uint32_t&) noexcept;
	template std::size_t Hash(const std::int64_t&) noexcept;
	template std::size_t Hash(const std::uint64_t&) noexcept;
	template std::size_t Hash(const REX::Float32&) noexcept;
	template std::size_t Hash(const REX::Float64&) noexcept;
	template std::size_t Hash(const REX::Float128&) noexcept;
	template std::size_t Hash(const std::string&) noexcept;
	template std::size_t Hash(const std::wstring&) noexcept;
	template std::size_t Hash(const std::string_view&) noexcept;
	template std::size_t Hash(const std::wstring_view&) noexcept;
	template std::size_t Hash(const std::nullptr_t&) noexcept;
	template std::size_t Hash(void* const&) noexcept;
	template std::size_t Hash(const void* const&) noexcept;

	template std::size_t HashIgnoreCase(std::string_view) noexcept;
	template std::size_t HashIgnoreCase(std::wstring_view) noexcept;
}
