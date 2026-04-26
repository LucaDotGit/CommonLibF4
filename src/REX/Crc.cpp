#include "REX/Crc.hpp"

namespace REX
{
	template auto CreateCrcTable<std::uint32_t>(std::uint32_t a_polynomial) noexcept -> std::array<std::uint32_t, 0x100>;
	template auto CreateCrcTable<std::uint64_t>(std::uint64_t a_polynomial) noexcept -> std::array<std::uint64_t, 0x100>;

	template std::uint32_t GenerateCrcHash<std::byte, std::uint32_t>(std::span<const std::byte> a_data, std::span<const std::uint32_t, CRC_TABLE_SIZE> a_table, std::uint32_t a_initValue, std::uint32_t a_xorOut) noexcept;
	template std::uint32_t GenerateCrcHash<char, std::uint32_t>(std::span<const char> a_data, std::span<const std::uint32_t, CRC_TABLE_SIZE> a_table, std::uint32_t a_initValue, std::uint32_t a_xorOut) noexcept;

	template std::uint64_t GenerateCrcHash<std::byte, std::uint64_t>(std::span<const std::byte> a_data, std::span<const std::uint64_t, CRC_TABLE_SIZE> a_table, std::uint64_t a_initValue, std::uint64_t a_xorOut) noexcept;
	template std::uint64_t GenerateCrcHash<char, std::uint64_t>(std::span<const char> a_data, std::span<const std::uint64_t, CRC_TABLE_SIZE> a_table, std::uint64_t a_initValue, std::uint64_t a_xorOut) noexcept;
}

namespace REX::Impl
{
	template std::uint32_t GenerateCrc32Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	template std::uint32_t GenerateCrc32Hash<char>(std::span<const char> a_data) noexcept;

	template std::uint64_t GenerateCrc64Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	template std::uint64_t GenerateCrc64Hash<char>(std::span<const char> a_data) noexcept;
}

namespace REX
{
	template struct Crc32<bool>;
	template struct Crc32<char>;
	template struct Crc32<wchar_t>;
	template struct Crc32<char8_t>;
	template struct Crc32<char16_t>;
	template struct Crc32<char32_t>;
	template struct Crc32<std::int8_t>;
	template struct Crc32<std::uint8_t>;
	template struct Crc32<std::int16_t>;
	template struct Crc32<std::uint16_t>;
	template struct Crc32<std::int32_t>;
	template struct Crc32<std::uint32_t>;
	template struct Crc32<std::int64_t>;
	template struct Crc32<std::uint64_t>;
	template struct Crc32<REX::Float32>;
	template struct Crc32<REX::Float64>;
	template struct Crc32<REX::Float128>;
	template struct Crc32<std::string>;
	template struct Crc32<std::wstring>;
	template struct Crc32<std::string_view>;
	template struct Crc32<std::wstring_view>;
	template struct Crc32<std::nullptr_t>;
	template struct Crc32<void*>;
	template struct Crc32<const void*>;

	template std::uint32_t HashCrc32(const bool&) noexcept;
	template std::uint32_t HashCrc32(const char&) noexcept;
	template std::uint32_t HashCrc32(const wchar_t&) noexcept;
	template std::uint32_t HashCrc32(const char8_t&) noexcept;
	template std::uint32_t HashCrc32(const char16_t&) noexcept;
	template std::uint32_t HashCrc32(const char32_t&) noexcept;
	template std::uint32_t HashCrc32(const std::int8_t&) noexcept;
	template std::uint32_t HashCrc32(const std::uint8_t&) noexcept;
	template std::uint32_t HashCrc32(const std::int16_t&) noexcept;
	template std::uint32_t HashCrc32(const std::uint16_t&) noexcept;
	template std::uint32_t HashCrc32(const std::int32_t&) noexcept;
	template std::uint32_t HashCrc32(const std::uint32_t&) noexcept;
	template std::uint32_t HashCrc32(const std::int64_t&) noexcept;
	template std::uint32_t HashCrc32(const std::uint64_t&) noexcept;
	template std::uint32_t HashCrc32(const REX::Float32&) noexcept;
	template std::uint32_t HashCrc32(const REX::Float64&) noexcept;
	template std::uint32_t HashCrc32(const REX::Float128&) noexcept;
	template std::uint32_t HashCrc32(const std::string&) noexcept;
	template std::uint32_t HashCrc32(const std::wstring&) noexcept;
	template std::uint32_t HashCrc32(const std::string_view&) noexcept;
	template std::uint32_t HashCrc32(const std::wstring_view&) noexcept;
	template std::uint32_t HashCrc32(const std::nullptr_t&) noexcept;
	template std::uint32_t HashCrc32(void* const&) noexcept;
	template std::uint32_t HashCrc32(const void* const&) noexcept;

	static_assert(HashCrc32(""sv) == std::numeric_limits<std::uint32_t>::min());
	static_assert(HashCrc32("123456789"sv) == 0xCBF43926ui32);

	template struct Crc64<bool>;
	template struct Crc64<char>;
	template struct Crc64<wchar_t>;
	template struct Crc64<char8_t>;
	template struct Crc64<char16_t>;
	template struct Crc64<char32_t>;
	template struct Crc64<std::int8_t>;
	template struct Crc64<std::uint8_t>;
	template struct Crc64<std::int16_t>;
	template struct Crc64<std::uint16_t>;
	template struct Crc64<std::int32_t>;
	template struct Crc64<std::uint32_t>;
	template struct Crc64<std::int64_t>;
	template struct Crc64<std::uint64_t>;
	template struct Crc64<REX::Float32>;
	template struct Crc64<REX::Float64>;
	template struct Crc64<REX::Float128>;
	template struct Crc64<std::string>;
	template struct Crc64<std::wstring>;
	template struct Crc64<std::string_view>;
	template struct Crc64<std::wstring_view>;
	template struct Crc64<std::nullptr_t>;
	template struct Crc64<void*>;
	template struct Crc64<const void*>;

	template std::uint64_t HashCrc64(const bool&) noexcept;
	template std::uint64_t HashCrc64(const char&) noexcept;
	template std::uint64_t HashCrc64(const wchar_t&) noexcept;
	template std::uint64_t HashCrc64(const char8_t&) noexcept;
	template std::uint64_t HashCrc64(const char16_t&) noexcept;
	template std::uint64_t HashCrc64(const char32_t&) noexcept;
	template std::uint64_t HashCrc64(const std::int8_t&) noexcept;
	template std::uint64_t HashCrc64(const std::uint8_t&) noexcept;
	template std::uint64_t HashCrc64(const std::int16_t&) noexcept;
	template std::uint64_t HashCrc64(const std::uint16_t&) noexcept;
	template std::uint64_t HashCrc64(const std::int32_t&) noexcept;
	template std::uint64_t HashCrc64(const std::uint32_t&) noexcept;
	template std::uint64_t HashCrc64(const std::int64_t&) noexcept;
	template std::uint64_t HashCrc64(const std::uint64_t&) noexcept;
	template std::uint64_t HashCrc64(const REX::Float32&) noexcept;
	template std::uint64_t HashCrc64(const REX::Float64&) noexcept;
	template std::uint64_t HashCrc64(const REX::Float128&) noexcept;
	template std::uint64_t HashCrc64(const std::string&) noexcept;
	template std::uint64_t HashCrc64(const std::wstring&) noexcept;
	template std::uint64_t HashCrc64(const std::string_view&) noexcept;
	template std::uint64_t HashCrc64(const std::wstring_view&) noexcept;
	template std::uint64_t HashCrc64(const std::nullptr_t&) noexcept;
	template std::uint64_t HashCrc64(void* const&) noexcept;
	template std::uint64_t HashCrc64(const void* const&) noexcept;

	static_assert(HashCrc64(""sv) == std::numeric_limits<std::uint64_t>::min());
	static_assert(HashCrc64("123456789"sv) == 0x995DC9BBDF1939FAui64);
}
