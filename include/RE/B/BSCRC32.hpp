#pragma once

namespace RE::Impl
{
	inline constexpr auto CRC32_POLYNOMIAL = 0xEDB88320ui32; // reflected from 0x04C11DB7
	inline constexpr auto CRC32_INIT_VALUE = std::numeric_limits<std::uint32_t>::min();
	inline constexpr auto CRC32_XOR_OUT = std::numeric_limits<std::uint32_t>::min();

	inline constexpr auto CRC32_TABLE = REX::CreateCrcTable<std::uint32_t>(CRC32_POLYNOMIAL);

	template <class T>
	[[nodiscard]] __forceinline constexpr std::uint32_t GenerateCRC32Hash(std::span<const T> a_data) noexcept
		requires(sizeof(T) == sizeof(std::byte))
	{
		return REX::GenerateCrcHash(a_data, std::span(CRC32_TABLE), CRC32_INIT_VALUE, CRC32_XOR_OUT);
	}

	extern template std::uint32_t GenerateCRC32Hash<std::byte>(std::span<const std::byte> a_data) noexcept;
	extern template std::uint32_t GenerateCRC32Hash<char>(std::span<const char> a_data) noexcept;
}

namespace RE
{
	template <class Key>
	struct BSCRC32;

	template <class T>
	concept crc32_hashable =
		std::is_invocable_r_v<
			std::uint32_t, BSCRC32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc32_hashable =
		std::is_nothrow_invocable_r_v<
			std::uint32_t, BSCRC32<std::decay_t<T>>, T>;

	template <class Key>
	struct BSCRC32
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(Key a_data) const noexcept
			requires(std::is_arithmetic_v<Key> || std::is_enum_v<Key> || std::is_pointer_v<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCRC32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct BSCRC32<std::nullptr_t>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::nullptr_t) const noexcept
		{
			static constexpr auto HASH = std::invoke(BSCRC32<std::uintptr_t>(), 0);
			return HASH;
		}
	};

	template <>
	struct BSCRC32<std::basic_string<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string<char>& a_key) const noexcept
		{
			return Impl::GenerateCRC32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct BSCRC32<std::basic_string<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCRC32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <>
	struct BSCRC32<std::basic_string_view<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string_view<char>& a_key) const noexcept
		{
			return Impl::GenerateCRC32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct BSCRC32<std::basic_string_view<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string_view<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateCRC32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <class T, std::size_t N>
	struct BSCRC32<std::span<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::span<T, N> a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCRC32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(a_key);
				return Impl::GenerateCRC32Hash(bytes);
			}
		}
	};

	template <class T, std::size_t N>
	struct BSCRC32<std::array<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::array<T, N>& a_key) const noexcept
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateCRC32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(std::span<const T>(a_key));
				return Impl::GenerateCRC32Hash(bytes);
			}
		}
	};

	template <crc32_hashable T>
	[[nodiscard]] constexpr std::uint32_t HashCRC32(const T& a_key) //
		noexcept(nothrow_crc32_hashable<T>)
	{
		return std::invoke(BSCRC32<std::decay_t<T>>(), a_key);
	}

	extern template struct BSCRC32<bool>;
	extern template struct BSCRC32<char>;
	extern template struct BSCRC32<wchar_t>;
	extern template struct BSCRC32<char8_t>;
	extern template struct BSCRC32<char16_t>;
	extern template struct BSCRC32<char32_t>;
	extern template struct BSCRC32<std::int8_t>;
	extern template struct BSCRC32<std::uint8_t>;
	extern template struct BSCRC32<std::int16_t>;
	extern template struct BSCRC32<std::uint16_t>;
	extern template struct BSCRC32<std::int32_t>;
	extern template struct BSCRC32<std::uint32_t>;
	extern template struct BSCRC32<std::int64_t>;
	extern template struct BSCRC32<std::uint64_t>;
	extern template struct BSCRC32<REX::Float32>;
	extern template struct BSCRC32<REX::Float64>;
	extern template struct BSCRC32<REX::Float128>;
	extern template struct BSCRC32<std::string>;
	extern template struct BSCRC32<std::wstring>;
	extern template struct BSCRC32<std::string_view>;
	extern template struct BSCRC32<std::wstring_view>;
	extern template struct BSCRC32<std::nullptr_t>;
	extern template struct BSCRC32<void*>;
	extern template struct BSCRC32<const void*>;

	extern template std::uint32_t HashCRC32(const bool&) noexcept;
	extern template std::uint32_t HashCRC32(const char&) noexcept;
	extern template std::uint32_t HashCRC32(const wchar_t&) noexcept;
	extern template std::uint32_t HashCRC32(const char8_t&) noexcept;
	extern template std::uint32_t HashCRC32(const char16_t&) noexcept;
	extern template std::uint32_t HashCRC32(const char32_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::int8_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::uint8_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::int16_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::uint16_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::int32_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::uint32_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::int64_t&) noexcept;
	extern template std::uint32_t HashCRC32(const std::uint64_t&) noexcept;
	extern template std::uint32_t HashCRC32(const REX::Float32&) noexcept;
	extern template std::uint32_t HashCRC32(const REX::Float64&) noexcept;
	extern template std::uint32_t HashCRC32(const REX::Float128&) noexcept;
	extern template std::uint32_t HashCRC32(const std::string&) noexcept;
	extern template std::uint32_t HashCRC32(const std::wstring&) noexcept;
	extern template std::uint32_t HashCRC32(const std::string_view&) noexcept;
	extern template std::uint32_t HashCRC32(const std::wstring_view&) noexcept;
	extern template std::uint32_t HashCRC32(const std::nullptr_t&) noexcept;
	extern template std::uint32_t HashCRC32(void* const&) noexcept;
	extern template std::uint32_t HashCRC32(const void* const&) noexcept;
}
