#pragma once

namespace RE::Impl
{
	inline constexpr auto CRC32_POLYNOMIAL = static_cast<std::uint32_t>(0xEDB8'8320); // reflected from 0x04C11DB7
	inline constexpr auto CRC32_INIT_VALUE = std::numeric_limits<std::uint32_t>::min();
	inline constexpr auto CRC32_XOR_OUT = std::numeric_limits<std::uint32_t>::min();

	inline constexpr auto CRC32_TABLE = REX::CreateCrcTable<std::uint32_t>(CRC32_POLYNOMIAL);

	template <class T, std::size_t N>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto GenerateCRC32Hash(std::span<const T, N> a_span) noexcept -> std::uint32_t
		requires(sizeof(T) == sizeof(std::byte))
	{
		return REX::GenerateCrcHash(a_span, std::span(CRC32_TABLE), CRC32_INIT_VALUE, CRC32_XOR_OUT);
	}
}

namespace RE
{
	template <class Key>
	struct BSCRC32;

	template <class T>
	concept crc32_hashable = std::is_invocable_r_v<std::uint32_t, BSCRC32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc32_hashable = std::is_nothrow_invocable_r_v<std::uint32_t, BSCRC32<std::decay_t<T>>, T>;

	template <class Key>
	struct BSCRC32
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(Key a_data) const noexcept -> std::uint32_t
			requires(REX::arithmetic<Key> || REX::enumeration<Key> || REX::pointer<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCRC32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct BSCRC32<std::nullptr_t>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::nullptr_t) const noexcept -> std::uint32_t
		{
			static constexpr auto EMPTY_HASH = std::invoke(BSCRC32<std::uintptr_t>(), 0);
			return EMPTY_HASH;
		}
	};

	template <class CharT, class Traits, class Allocator>
	struct BSCRC32<std::basic_string<CharT, Traits, Allocator>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::basic_string<CharT, Traits, Allocator>& a_key) const noexcept
			-> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCRC32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCRC32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class CharT, class Traits>
	struct BSCRC32<std::basic_string_view<CharT, Traits>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT, Traits> a_key) const noexcept -> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCRC32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCRC32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class T, std::size_t N>
	struct BSCRC32<std::span<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::span<T, N> a_key) const noexcept -> std::uint32_t
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
		[[nodiscard]]
		constexpr auto operator()(const std::array<T, N>& a_key) const noexcept -> std::uint32_t
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
	[[nodiscard]]
	constexpr auto HashCRC32(const T& a_key) noexcept(nothrow_crc32_hashable<T>) -> std::uint32_t
	{
		return std::invoke(BSCRC32<std::decay_t<T>>(), a_key);
	}

	static_assert(HashCRC32(""sv) == std::numeric_limits<std::uint32_t>::min());
	static_assert(HashCRC32("123456789"sv) == static_cast<std::uint32_t>(0x2DFD'2D88));
}
