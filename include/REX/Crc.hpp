#pragma once

#include "REX/Concepts.hpp"

namespace REX
{
	// Source: https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Computation

	inline constexpr auto CRC_TABLE_SIZE = static_cast<std::size_t>(0x100);

	template <REX::integer T>
	[[nodiscard]] constexpr auto CreateCrcTable(T a_polynomial) noexcept -> std::array<T, CRC_TABLE_SIZE>
	{
		auto table = std::array<T, CRC_TABLE_SIZE>();
		for (auto i = static_cast<std::size_t>(0); i < table.size(); i++) {
			auto crc = i;
			for (auto j = static_cast<std::size_t>(0); j < 8; j++) {
				crc = (crc & 1) ? ((crc >> 1) ^ a_polynomial) : (crc >> 1);
			}

			table[i] = crc;
		}

		return table;
	}

	extern template auto CreateCrcTable<std::uint32_t>(std::uint32_t a_polynomial) noexcept -> std::array<std::uint32_t, CRC_TABLE_SIZE>;
	extern template auto CreateCrcTable<std::uint64_t>(std::uint64_t a_polynomial) noexcept -> std::array<std::uint64_t, CRC_TABLE_SIZE>;

	template <class T, REX::integer U>
	[[nodiscard]] constexpr U GenerateCrcHash(std::span<const T> a_data, std::span<const U, CRC_TABLE_SIZE> a_table, U a_initValue, U a_xorOut) noexcept
		requires(sizeof(T) == sizeof(std::byte))
	{
		auto result = a_initValue;
		for (const auto byte : a_data) {
			const auto tableIndex = (result ^ static_cast<std::uint8_t>(byte)) & static_cast<decltype(result)>(std::numeric_limits<std::uint8_t>::max());
			const auto tableValue = a_table[tableIndex];
			result = (result >> 8) ^ tableValue;
		}

		return result ^ a_xorOut;
	}

	extern template std::uint32_t GenerateCrcHash<std::byte, std::uint32_t>(std::span<const std::byte> a_data, std::span<const std::uint32_t, CRC_TABLE_SIZE> a_table, std::uint32_t a_initValue, std::uint32_t a_xorOut) noexcept;
	extern template std::uint32_t GenerateCrcHash<char, std::uint32_t>(std::span<const char> a_data, std::span<const std::uint32_t, CRC_TABLE_SIZE> a_table, std::uint32_t a_initValue, std::uint32_t a_xorOut) noexcept;

	extern template std::uint64_t GenerateCrcHash<std::byte, std::uint64_t>(std::span<const std::byte> a_data, std::span<const std::uint64_t, CRC_TABLE_SIZE> a_table, std::uint64_t a_initValue, std::uint64_t a_xorOut) noexcept;
	extern template std::uint64_t GenerateCrcHash<char, std::uint64_t>(std::span<const char> a_data, std::span<const std::uint64_t, CRC_TABLE_SIZE> a_table, std::uint64_t a_initValue, std::uint64_t a_xorOut) noexcept;
}

namespace REX::Impl
{
	// Source: https://emn178.github.io/online-tools/crc

	inline constexpr auto CRC32_ISO_POLYNOMIAL = 0xEDB88320ui32; // reflected from 0x04C11DB7
	inline constexpr auto CRC32_ISO_INIT_VALUE = std::numeric_limits<std::uint32_t>::max();
	inline constexpr auto CRC32_ISO_XOR_OUT = std::numeric_limits<std::uint32_t>::max();

	inline constexpr auto CRC64_XZ_POLYNOMIAL = 0xC96C5795D7870F42ui64; // reflected from 0x42F0E1EBA9EA3693
	inline constexpr auto CRC64_XZ_INIT_VALUE = std::numeric_limits<std::uint64_t>::max();
	inline constexpr auto CRC64_XZ_XOR_OUT = std::numeric_limits<std::uint64_t>::max();

	inline constexpr auto CRC32_ISO_TABLE = CreateCrcTable<std::uint32_t>(CRC32_ISO_POLYNOMIAL);
	inline constexpr auto CRC64_XZ_TABLE = CreateCrcTable<std::uint64_t>(CRC64_XZ_POLYNOMIAL);

	template <class T>
	[[nodiscard]] __forceinline constexpr std::uint32_t GenerateCrc32Hash(std::span<const T> a_data) noexcept
	{
		return GenerateCrcHash(a_data, std::span(CRC32_ISO_TABLE), CRC32_ISO_INIT_VALUE, CRC32_ISO_XOR_OUT);
	}

	extern template std::uint32_t GenerateCrc32Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	extern template std::uint32_t GenerateCrc32Hash<char>(std::span<const char> a_data) noexcept;

	template <class T>
	[[nodiscard]] __forceinline constexpr std::uint64_t GenerateCrc64Hash(std::span<const T> a_data) noexcept
	{
		return GenerateCrcHash(a_data, std::span(CRC64_XZ_TABLE), CRC64_XZ_INIT_VALUE, CRC64_XZ_XOR_OUT);
	}

	extern template std::uint64_t GenerateCrc64Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	extern template std::uint64_t GenerateCrc64Hash<char>(std::span<const char> a_data) noexcept;
}

namespace REX
{
	template <class Key>
	struct Crc32;

	template <class T>
	concept crc32_hashable =
		std::is_invocable_r_v<
			std::uint32_t, Crc32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc32_hashable =
		std::is_nothrow_invocable_r_v<
			std::uint32_t, Crc32<std::decay_t<T>>, T>;

	template <class Key>
	struct Crc32
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(Key a_data) const noexcept
			requires(std::is_arithmetic_v<Key> || std::is_enum_v<Key> || std::is_pointer_v<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCrc32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Crc32<std::nullptr_t>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::nullptr_t) const noexcept
		{
			static constexpr auto HASH = std::invoke(Crc32<std::uintptr_t>(), 0);
			return HASH;
		}
	};

	template <>
	struct Crc32<std::basic_string<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string<char>& a_key) const noexcept
		{
			return Impl::GenerateCrc32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Crc32<std::basic_string<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCrc32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <>
	struct Crc32<std::basic_string_view<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string_view<char>& a_key) const noexcept
		{
			return Impl::GenerateCrc32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Crc32<std::basic_string_view<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string_view<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCrc32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <class T, std::size_t N>
	struct Crc32<std::span<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::span<T, N> a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCrc32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(a_key);
				return Impl::GenerateCrc32Hash(bytes);
			}
		}
	};

	template <class T, std::size_t N>
	struct Crc32<std::array<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::array<T, N>& a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCrc32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(std::span<const T>(a_key));
				return Impl::GenerateCrc32Hash(bytes);
			}
		}
	};

	template <crc32_hashable T>
	[[nodiscard]] constexpr std::uint32_t HashCrc32(const T& a_key) //
		noexcept(nothrow_crc32_hashable<T>)
	{
		return std::invoke(Crc32<std::decay_t<T>>(), a_key);
	}

	extern template struct Crc32<bool>;
	extern template struct Crc32<char>;
	extern template struct Crc32<wchar_t>;
	extern template struct Crc32<char8_t>;
	extern template struct Crc32<char16_t>;
	extern template struct Crc32<char32_t>;
	extern template struct Crc32<std::int8_t>;
	extern template struct Crc32<std::uint8_t>;
	extern template struct Crc32<std::int16_t>;
	extern template struct Crc32<std::uint16_t>;
	extern template struct Crc32<std::int32_t>;
	extern template struct Crc32<std::uint32_t>;
	extern template struct Crc32<std::int64_t>;
	extern template struct Crc32<std::uint64_t>;
	extern template struct Crc32<REX::Float32>;
	extern template struct Crc32<REX::Float64>;
	extern template struct Crc32<REX::Float128>;
	extern template struct Crc32<std::string>;
	extern template struct Crc32<std::wstring>;
	extern template struct Crc32<std::string_view>;
	extern template struct Crc32<std::wstring_view>;
	extern template struct Crc32<std::nullptr_t>;
	extern template struct Crc32<void*>;
	extern template struct Crc32<const void*>;

	extern template std::uint32_t HashCrc32(const bool&) noexcept;
	extern template std::uint32_t HashCrc32(const char&) noexcept;
	extern template std::uint32_t HashCrc32(const wchar_t&) noexcept;
	extern template std::uint32_t HashCrc32(const char8_t&) noexcept;
	extern template std::uint32_t HashCrc32(const char16_t&) noexcept;
	extern template std::uint32_t HashCrc32(const char32_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::int8_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::uint8_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::int16_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::uint16_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::int32_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::uint32_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::int64_t&) noexcept;
	extern template std::uint32_t HashCrc32(const std::uint64_t&) noexcept;
	extern template std::uint32_t HashCrc32(const REX::Float32&) noexcept;
	extern template std::uint32_t HashCrc32(const REX::Float64&) noexcept;
	extern template std::uint32_t HashCrc32(const REX::Float128&) noexcept;
	extern template std::uint32_t HashCrc32(const std::string&) noexcept;
	extern template std::uint32_t HashCrc32(const std::wstring&) noexcept;
	extern template std::uint32_t HashCrc32(const std::string_view&) noexcept;
	extern template std::uint32_t HashCrc32(const std::wstring_view&) noexcept;
	extern template std::uint32_t HashCrc32(const std::nullptr_t&) noexcept;
	extern template std::uint32_t HashCrc32(void* const&) noexcept;
	extern template std::uint32_t HashCrc32(const void* const&) noexcept;

	template <class Key>
	struct Crc64;

	template <class T>
	concept crc64_hashable =
		std::is_invocable_r_v<
			std::uint64_t, Crc64<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc64_hashable =
		std::is_nothrow_invocable_r_v<
			std::uint64_t, Crc64<std::decay_t<T>>, T>;

	template <class Key>
	struct Crc64
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(Key a_data) const noexcept
			requires(std::is_arithmetic_v<Key> || std::is_enum_v<Key> || std::is_pointer_v<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCrc64Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Crc64<std::nullptr_t>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(std::nullptr_t) const noexcept
		{
			static constexpr auto HASH = std::invoke(Crc64<std::uintptr_t>(), 0);
			return HASH;
		}
	};

	template <>
	struct Crc64<std::basic_string<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(const std::basic_string<char>& a_key) const noexcept
		{
			return Impl::GenerateCrc64Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Crc64<std::basic_string<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint64_t operator()(const std::basic_string<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCrc64Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <>
	struct Crc64<std::basic_string_view<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(const std::basic_string_view<char>& a_key) const noexcept
		{
			return Impl::GenerateCrc64Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Crc64<std::basic_string_view<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint64_t operator()(const std::basic_string_view<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCrc64Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <class T, std::size_t N>
	struct Crc64<std::span<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(std::span<T, N> a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCrc64Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(a_key);
				return Impl::GenerateCrc64Hash(bytes);
			}
		}
	};

	template <class T, std::size_t N>
	struct Crc64<std::array<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(const std::array<T, N>& a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCrc64Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(std::span<const T>(a_key));
				return Impl::GenerateCrc64Hash(bytes);
			}
		}
	};

	template <crc64_hashable T>
	[[nodiscard]] constexpr std::uint64_t HashCrc64(const T& a_key) //
		noexcept(nothrow_crc64_hashable<T>)
	{
		return std::invoke(Crc64<std::decay_t<T>>(), a_key);
	}

	extern template struct Crc64<bool>;
	extern template struct Crc64<char>;
	extern template struct Crc64<wchar_t>;
	extern template struct Crc64<char8_t>;
	extern template struct Crc64<char16_t>;
	extern template struct Crc64<char32_t>;
	extern template struct Crc64<std::int8_t>;
	extern template struct Crc64<std::uint8_t>;
	extern template struct Crc64<std::int16_t>;
	extern template struct Crc64<std::uint16_t>;
	extern template struct Crc64<std::int32_t>;
	extern template struct Crc64<std::uint32_t>;
	extern template struct Crc64<std::int64_t>;
	extern template struct Crc64<std::uint64_t>;
	extern template struct Crc64<REX::Float32>;
	extern template struct Crc64<REX::Float64>;
	extern template struct Crc64<REX::Float128>;
	extern template struct Crc64<std::string>;
	extern template struct Crc64<std::wstring>;
	extern template struct Crc64<std::string_view>;
	extern template struct Crc64<std::wstring_view>;
	extern template struct Crc64<std::nullptr_t>;
	extern template struct Crc64<void*>;
	extern template struct Crc64<const void*>;

	extern template std::uint64_t HashCrc64(const bool&) noexcept;
	extern template std::uint64_t HashCrc64(const char&) noexcept;
	extern template std::uint64_t HashCrc64(const wchar_t&) noexcept;
	extern template std::uint64_t HashCrc64(const char8_t&) noexcept;
	extern template std::uint64_t HashCrc64(const char16_t&) noexcept;
	extern template std::uint64_t HashCrc64(const char32_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::int8_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::uint8_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::int16_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::uint16_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::int32_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::uint32_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::int64_t&) noexcept;
	extern template std::uint64_t HashCrc64(const std::uint64_t&) noexcept;
	extern template std::uint64_t HashCrc64(const REX::Float32&) noexcept;
	extern template std::uint64_t HashCrc64(const REX::Float64&) noexcept;
	extern template std::uint64_t HashCrc64(const REX::Float128&) noexcept;
	extern template std::uint64_t HashCrc64(const std::string&) noexcept;
	extern template std::uint64_t HashCrc64(const std::wstring&) noexcept;
	extern template std::uint64_t HashCrc64(const std::string_view&) noexcept;
	extern template std::uint64_t HashCrc64(const std::wstring_view&) noexcept;
	extern template std::uint64_t HashCrc64(const std::nullptr_t&) noexcept;
	extern template std::uint64_t HashCrc64(void* const&) noexcept;
	extern template std::uint64_t HashCrc64(const void* const&) noexcept;
}
