#include "RE/B/BSCRC32.hpp"

namespace RE::Impl
{
	template std::uint32_t GenerateCRC32Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	template std::uint32_t GenerateCRC32Hash<char>(std::span<const char> a_data) noexcept;
}

namespace RE
{
	template struct BSCRC32<bool>;
	template struct BSCRC32<char>;
	template struct BSCRC32<wchar_t>;
	template struct BSCRC32<char8_t>;
	template struct BSCRC32<char16_t>;
	template struct BSCRC32<char32_t>;
	template struct BSCRC32<std::int8_t>;
	template struct BSCRC32<std::uint8_t>;
	template struct BSCRC32<std::int16_t>;
	template struct BSCRC32<std::uint16_t>;
	template struct BSCRC32<std::int32_t>;
	template struct BSCRC32<std::uint32_t>;
	template struct BSCRC32<std::int64_t>;
	template struct BSCRC32<std::uint64_t>;
	template struct BSCRC32<REX::Float32>;
	template struct BSCRC32<REX::Float64>;
	template struct BSCRC32<REX::Float128>;
	template struct BSCRC32<std::string>;
	template struct BSCRC32<std::wstring>;
	template struct BSCRC32<std::string_view>;
	template struct BSCRC32<std::wstring_view>;
	template struct BSCRC32<std::nullptr_t>;
	template struct BSCRC32<void*>;
	template struct BSCRC32<const void*>;

	template std::uint32_t HashCRC32(const bool&) noexcept;
	template std::uint32_t HashCRC32(const char&) noexcept;
	template std::uint32_t HashCRC32(const wchar_t&) noexcept;
	template std::uint32_t HashCRC32(const char8_t&) noexcept;
	template std::uint32_t HashCRC32(const char16_t&) noexcept;
	template std::uint32_t HashCRC32(const char32_t&) noexcept;
	template std::uint32_t HashCRC32(const std::int8_t&) noexcept;
	template std::uint32_t HashCRC32(const std::uint8_t&) noexcept;
	template std::uint32_t HashCRC32(const std::int16_t&) noexcept;
	template std::uint32_t HashCRC32(const std::uint16_t&) noexcept;
	template std::uint32_t HashCRC32(const std::int32_t&) noexcept;
	template std::uint32_t HashCRC32(const std::uint32_t&) noexcept;
	template std::uint32_t HashCRC32(const std::int64_t&) noexcept;
	template std::uint32_t HashCRC32(const std::uint64_t&) noexcept;
	template std::uint32_t HashCRC32(const REX::Float32&) noexcept;
	template std::uint32_t HashCRC32(const REX::Float64&) noexcept;
	template std::uint32_t HashCRC32(const REX::Float128&) noexcept;
	template std::uint32_t HashCRC32(const std::string&) noexcept;
	template std::uint32_t HashCRC32(const std::wstring&) noexcept;
	template std::uint32_t HashCRC32(const std::string_view&) noexcept;
	template std::uint32_t HashCRC32(const std::wstring_view&) noexcept;
	template std::uint32_t HashCRC32(const std::nullptr_t&) noexcept;
	template std::uint32_t HashCRC32(void* const&) noexcept;
	template std::uint32_t HashCRC32(const void* const&) noexcept;

	static_assert(HashCRC32(0) == std::numeric_limits<std::uint32_t>::min());
	static_assert(HashCRC32("123456789"sv) == 0x2DFD2D88);
}
