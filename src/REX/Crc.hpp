#pragma once

#include "REX/Concepts.hpp"
#include "REX/Macros.hpp"

namespace REX
{
	// Source: https://en.wikipedia.org/wiki/Cyclic_redundancy_check#Computation

	inline constexpr auto CRC_TABLE_SIZE = static_cast<std::size_t>(0x100);

	template <REX::integer T>
	[[nodiscard]]
	constexpr auto CreateCrcTable(T a_polynomial) noexcept -> std::array<T, CRC_TABLE_SIZE>
	{
		auto table = std::array<T, CRC_TABLE_SIZE>();
		for (auto i = static_cast<std::size_t>(0); i < table.size(); i++) {
			auto crc = static_cast<T>(i);
			for (auto j = static_cast<std::size_t>(0); j < 8; j++) {
				crc = (crc & 1) ? ((crc >> 1) ^ a_polynomial) : (crc >> 1);
			}

			table[i] = crc;
		}

		return table;
	}

	template <class T, REX::integer U, std::size_t N>
	[[nodiscard]]
	constexpr auto GenerateCrcHash(
		std::span<const T, N> a_span,
		std::span<const U, CRC_TABLE_SIZE> a_table,
		U a_initValue,
		U a_xorOut) noexcept -> U
		requires(sizeof(T) == sizeof(std::byte))
	{
		auto result = a_initValue;
		for (const auto element : a_span) {
			const auto tableIndex = (result ^ static_cast<std::uint8_t>(element)) &
									static_cast<decltype(result)>(std::numeric_limits<std::uint8_t>::max());
			const auto tableValue = a_table[tableIndex];
			result = (result >> 8) ^ tableValue;
		}

		return result ^ a_xorOut;
	}
}

namespace REX::Impl
{
	// Source: https://emn178.github.io/online-tools/crc

	inline constexpr auto CRC32_ISO_POLYNOMIAL = static_cast<std::uint32_t>(0xEDB8'8320); // reflected from 0x04C11DB7
	inline constexpr auto CRC32_ISO_INIT_VALUE = std::numeric_limits<std::uint32_t>::max();
	inline constexpr auto CRC32_ISO_XOR_OUT = std::numeric_limits<std::uint32_t>::max();

	inline constexpr auto CRC64_XZ_POLYNOMIAL =
		static_cast<std::uint64_t>(0xC96C'5795'D787'0F42); // reflected from 0x42F0E1EBA9EA3693
	inline constexpr auto CRC64_XZ_INIT_VALUE = std::numeric_limits<std::uint64_t>::max();
	inline constexpr auto CRC64_XZ_XOR_OUT = std::numeric_limits<std::uint64_t>::max();

	inline constexpr auto CRC32_ISO_TABLE = CreateCrcTable<std::uint32_t>(CRC32_ISO_POLYNOMIAL);
	inline constexpr auto CRC64_XZ_TABLE = CreateCrcTable<std::uint64_t>(CRC64_XZ_POLYNOMIAL);

	template <class T, std::size_t N>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto GenerateCrc32Hash(std::span<const T, N> a_span) noexcept -> std::uint32_t
	{
		return GenerateCrcHash(a_span, std::span(CRC32_ISO_TABLE), CRC32_ISO_INIT_VALUE, CRC32_ISO_XOR_OUT);
	}

	template <class T, std::size_t N>
	[[nodiscard]] [[REX_ALWAYS_INLINE]]
	constexpr auto GenerateCrc64Hash(std::span<const T, N> a_span) noexcept -> std::uint64_t
	{
		return GenerateCrcHash(a_span, std::span(CRC64_XZ_TABLE), CRC64_XZ_INIT_VALUE, CRC64_XZ_XOR_OUT);
	}
}

namespace REX
{
	template <class Key>
	struct Crc32;

	template <class T>
	concept crc32_hashable = std::is_invocable_r_v<std::uint32_t, Crc32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc32_hashable = std::is_nothrow_invocable_r_v<std::uint32_t, Crc32<std::decay_t<T>>, T>;

	template <class Key>
	struct Crc32
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(Key a_data) const noexcept -> std::uint32_t
			requires(REX::arithmetic<Key> || REX::enumeration<Key> || REX::pointer<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCrc32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Crc32<std::nullptr_t>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::nullptr_t) const noexcept -> std::uint32_t
		{
			static constexpr auto EMPTY_HASH = std::invoke(Crc32<std::uintptr_t>(), 0);
			return EMPTY_HASH;
		}
	};

	template <class CharT, class Traits, class Allocator>
	struct Crc32<std::basic_string<CharT, Traits, Allocator>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::basic_string<CharT, Traits, Allocator>& a_key) const noexcept
			-> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCrc32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCrc32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class CharT, class Traits>
	struct Crc32<std::basic_string_view<CharT, Traits>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT, Traits> a_key) const noexcept -> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCrc32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCrc32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class T, std::size_t N>
	struct Crc32<std::span<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::span<T, N> a_key) const noexcept -> std::uint32_t
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
		[[nodiscard]]
		constexpr auto operator()(const std::array<T, N>& a_key) const noexcept -> std::uint32_t
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
	[[nodiscard]]
	constexpr auto HashCrc32(const T& a_key) noexcept(nothrow_crc32_hashable<T>) -> std::uint32_t
	{
		return std::invoke(Crc32<std::decay_t<T>>(), a_key);
	}

	static_assert(HashCrc32(""sv) == std::numeric_limits<std::uint32_t>::min());
	static_assert(HashCrc32("123456789"sv) == static_cast<std::uint32_t>(0xCBF4'3926));

	template <class Key>
	struct Crc64;

	template <class T>
	concept crc64_hashable = std::is_invocable_r_v<std::uint64_t, Crc64<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_crc64_hashable = std::is_nothrow_invocable_r_v<std::uint64_t, Crc64<std::decay_t<T>>, T>;

	template <class Key>
	struct Crc64
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(Key a_data) const noexcept -> std::uint64_t
			requires(REX::arithmetic<Key> || REX::enumeration<Key> || REX::pointer<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateCrc64Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Crc64<std::nullptr_t>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::nullptr_t) const noexcept -> std::uint64_t
		{
			static constexpr auto EMPTY_HASH = std::invoke(Crc64<std::uintptr_t>(), 0);
			return EMPTY_HASH;
		}
	};

	template <class CharT, class Traits, class Allocator>
	struct Crc64<std::basic_string<CharT, Traits, Allocator>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::basic_string<CharT, Traits, Allocator>& a_key) const noexcept
			-> std::uint64_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCrc64Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCrc64Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class CharT, class Traits>
	struct Crc64<std::basic_string_view<CharT, Traits>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT, Traits> a_key) const noexcept -> std::uint64_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateCrc64Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateCrc64Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class T, std::size_t N>
	struct Crc64<std::span<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::span<T, N> a_key) const noexcept -> std::uint64_t
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
		[[nodiscard]]
		constexpr auto operator()(const std::array<T, N>& a_key) const noexcept -> std::uint64_t
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
	[[nodiscard]]
	constexpr auto HashCrc64(const T& a_key) noexcept(nothrow_crc64_hashable<T>) -> std::uint64_t
	{
		return std::invoke(Crc64<std::decay_t<T>>(), a_key);
	}

	static_assert(HashCrc64(""sv) == std::numeric_limits<std::uint64_t>::min());
	static_assert(HashCrc64("123456789"sv) == static_cast<std::uint64_t>(0x995D'C9BB'DF19'39FA));
}
