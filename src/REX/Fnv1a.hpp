#pragma once

#include "REX/Concepts.hpp"

namespace REX::Impl
{
	// Source: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

	inline constexpr auto FNV1A_32_OFFSET_BASIS = static_cast<std::uint32_t>(0x811C'9DC5);
	inline constexpr auto FNV1A_32_PRIME = static_cast<std::uint32_t>(0x0100'0193);

	inline constexpr auto FNV1A_64_OFFSET_BASIS = static_cast<std::uint64_t>(0xCBF2'9CE4'8422'2325);
	inline constexpr auto FNV1A_64_PRIME = static_cast<std::uint64_t>(0x100'0000'01B3);

	template <class T, REX::integer U, std::size_t N>
	[[nodiscard]]
	constexpr auto GenerateFnv1aHash(std::span<const T, N> a_span, U a_offsetBasis, U a_prime) noexcept -> U
		requires(sizeof(T) == sizeof(std::byte))
	{
		auto result = a_offsetBasis;
		for (const auto byte : a_span) {
			result ^= static_cast<std::uint8_t>(byte);
			result *= a_prime;
		}

		return result;
	}

	template <class T, std::size_t N>
	[[nodiscard]]
	constexpr auto GenerateFnv1a32Hash(std::span<const T, N> a_span) noexcept -> std::uint32_t
	{
		return GenerateFnv1aHash(a_span, FNV1A_32_OFFSET_BASIS, FNV1A_32_PRIME);
	}

	template <class T, std::size_t N>
	[[nodiscard]]
	constexpr auto GenerateFnv1a64Hash(std::span<const T, N> a_span) noexcept -> std::uint64_t
	{
		return GenerateFnv1aHash(a_span, FNV1A_64_OFFSET_BASIS, FNV1A_64_PRIME);
	}
}

namespace REX
{
	template <class Key>
	struct Fnv1a32;

	template <class T>
	concept fnv1a32_hashable = std::is_invocable_r_v<std::uint32_t, Fnv1a32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_fnv1a32_hashable = std::is_nothrow_invocable_r_v<std::uint32_t, Fnv1a32<std::decay_t<T>>, T>;

	template <class Key>
	struct Fnv1a32
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(Key a_data) const noexcept -> std::uint32_t
			requires(REX::arithmetic<Key> || REX::enumeration<Key> || REX::pointer<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateFnv1a32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Fnv1a32<std::nullptr_t>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::nullptr_t) const noexcept -> std::uint32_t
		{
			static constexpr auto EMPTY_HASH = std::invoke(Fnv1a32<std::uintptr_t>(), 0);
			return EMPTY_HASH;
		}
	};

	template <class CharT, class Traits, class Allocator>
	struct Fnv1a32<std::basic_string<CharT, Traits, Allocator>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::basic_string<CharT, Traits, Allocator>& a_key) const noexcept
			-> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateFnv1a32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class CharT, class Traits>
	struct Fnv1a32<std::basic_string_view<CharT, Traits>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT, Traits> a_key) const noexcept -> std::uint32_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a32Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateFnv1a32Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a32<std::span<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::span<T, N> a_key) const noexcept -> std::uint32_t
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(a_key);
				return Impl::GenerateFnv1a32Hash(bytes);
			}
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a32<std::array<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::array<T, N>& a_key) const noexcept -> std::uint32_t
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a32Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(std::span<const T>(a_key));
				return Impl::GenerateFnv1a32Hash(bytes);
			}
		}
	};

	template <fnv1a32_hashable T>
	[[nodiscard]]
	constexpr auto HashFnv1a32(const T& a_key) noexcept(nothrow_fnv1a32_hashable<T>) -> std::uint32_t
	{
		return std::invoke(Fnv1a32<std::decay_t<T>>(), a_key);
	}

	static_assert(HashFnv1a32(""sv) == static_cast<std::uint32_t>(0x811C'9DC5));
	static_assert(HashFnv1a32("123456789"sv) == static_cast<std::uint32_t>(0xBB86'B11C));

	template <class Key>
	struct Fnv1a64;

	template <class T>
	concept fnv1a64_hashable = std::is_invocable_r_v<std::uint64_t, Fnv1a64<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_fnv1a64_hashable = std::is_nothrow_invocable_r_v<std::uint64_t, Fnv1a64<std::decay_t<T>>, T>;

	template <class Key>
	struct Fnv1a64
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(Key a_data) const noexcept -> std::uint64_t
			requires(REX::arithmetic<Key> || REX::enumeration<Key> || REX::pointer<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateFnv1a64Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Fnv1a64<std::nullptr_t>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::nullptr_t) const noexcept -> std::uint64_t
		{
			static constexpr auto EMPTY_HASH = std::invoke(Fnv1a64<std::uintptr_t>(), 0);
			return EMPTY_HASH;
		}
	};

	template <class CharT, class Traits, class Allocator>
	struct Fnv1a64<std::basic_string<CharT, Traits, Allocator>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::basic_string<CharT, Traits, Allocator>& a_key) const noexcept
			-> std::uint64_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a64Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateFnv1a64Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class CharT, class Traits>
	struct Fnv1a64<std::basic_string_view<CharT, Traits>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT, Traits> a_key) const noexcept -> std::uint64_t
		{
			if constexpr (sizeof(CharT) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a64Hash(std::span<const CharT>(a_key));
			}
			else {
				return Impl::GenerateFnv1a64Hash(
					std::span{reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(CharT)});
			}
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a64<std::span<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(std::span<T, N> a_key) const noexcept -> std::uint64_t
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a64Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(a_key);
				return Impl::GenerateFnv1a64Hash(bytes);
			}
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a64<std::array<T, N>>
	{
	public:
		[[nodiscard]]
		constexpr auto operator()(const std::array<T, N>& a_key) const noexcept -> std::uint64_t
		{
			if constexpr (sizeof(T) == sizeof(std::byte)) {
				return Impl::GenerateFnv1a64Hash(a_key);
			}
			else {
				const auto bytes = std::as_bytes(std::span<const T>(a_key));
				return Impl::GenerateFnv1a64Hash(bytes);
			}
		}
	};

	template <fnv1a64_hashable T>
	[[nodiscard]]
	constexpr auto HashFnv1a64(const T& a_key) noexcept(nothrow_fnv1a64_hashable<T>) -> std::uint64_t
	{
		return std::invoke(Fnv1a64<std::decay_t<T>>(), a_key);
	}

	static_assert(HashFnv1a64(""sv) == static_cast<std::uint64_t>(0xCBF2'9CE4'8422'2325));
	static_assert(HashFnv1a64("123456789"sv) == static_cast<std::uint64_t>(0x6D5'5739'23C6'CDFC));
}
