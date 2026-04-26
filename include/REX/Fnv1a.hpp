#pragma once

#include "REX/Concepts.hpp"

namespace REX::Impl
{
	// Source: https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

	inline constexpr auto FNV1A_32_OFFSET_BASIS = 0x811C9DC5ui32;
	inline constexpr auto FNV1A_32_PRIME = 0x01000193ui32;

	inline constexpr auto FNV1A_64_OFFSET_BASIS = 0xCBF29CE484222325ui64;
	inline constexpr auto FNV1A_64_PRIME = 0x100000001B3ui64;

	template <class T, REX::integer U>
	[[nodiscard]] constexpr U GenerateFnv1aHash(std::span<const T> a_data, U a_offsetBasis, U a_prime) noexcept
		requires(sizeof(T) == sizeof(std::byte))
	{
		auto result = a_offsetBasis;
		for (const auto byte : a_data) {
			result ^= static_cast<std::uint8_t>(byte);
			result *= a_prime;
		}

		return result;
	}

	template <class T>
	[[nodiscard]] constexpr std::uint32_t GenerateFnv1a32Hash(std::span<const T> a_data) noexcept
	{
		return GenerateFnv1aHash(a_data, FNV1A_32_OFFSET_BASIS, FNV1A_32_PRIME);
	}

	template <class T>
	[[nodiscard]] constexpr std::uint64_t GenerateFnv1a64Hash(std::span<const T> a_data) noexcept
	{
		return GenerateFnv1aHash(a_data, FNV1A_64_OFFSET_BASIS, FNV1A_64_PRIME);
	}
}

namespace REX
{
	template <class Key>
	struct Fnv1a32;

	template <class T>
	concept fnv1a32_hashable =
		std::is_invocable_r_v<
			std::uint32_t, Fnv1a32<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_fnv1a32_hashable =
		std::is_nothrow_invocable_r_v<
			std::uint32_t, Fnv1a32<std::decay_t<T>>, T>;

	template <class Key>
	struct Fnv1a32
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(Key a_data) const noexcept
			requires(std::is_arithmetic_v<Key> || std::is_enum_v<Key> || std::is_pointer_v<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateFnv1a32Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Fnv1a32<std::nullptr_t>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::nullptr_t) const noexcept
		{
			static constexpr auto HASH = std::invoke(Fnv1a32<std::uintptr_t>(), 0);
			return HASH;
		}
	};

	template <>
	struct Fnv1a32<std::basic_string<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string<char>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Fnv1a32<std::basic_string<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <>
	struct Fnv1a32<std::basic_string_view<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(const std::basic_string_view<char>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a32Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Fnv1a32<std::basic_string_view<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint32_t operator()(const std::basic_string_view<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a32Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a32<std::span<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint32_t operator()(std::span<T, N> a_key) const noexcept
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
		[[nodiscard]] constexpr std::uint32_t operator()(const std::array<T, N>& a_key) const noexcept
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
	[[nodiscard]] constexpr std::uint32_t HashFnv1a32(const T& a_key) //
		noexcept(nothrow_fnv1a32_hashable<T>)
	{
		return std::invoke(Fnv1a32<std::decay_t<T>>(), a_key);
	}

	extern template struct Fnv1a32<bool>;
	extern template struct Fnv1a32<char>;
	extern template struct Fnv1a32<wchar_t>;
	extern template struct Fnv1a32<char8_t>;
	extern template struct Fnv1a32<char16_t>;
	extern template struct Fnv1a32<char32_t>;
	extern template struct Fnv1a32<std::int8_t>;
	extern template struct Fnv1a32<std::uint8_t>;
	extern template struct Fnv1a32<std::int16_t>;
	extern template struct Fnv1a32<std::uint16_t>;
	extern template struct Fnv1a32<std::int32_t>;
	extern template struct Fnv1a32<std::uint32_t>;
	extern template struct Fnv1a32<std::int64_t>;
	extern template struct Fnv1a32<std::uint64_t>;
	extern template struct Fnv1a32<REX::Float32>;
	extern template struct Fnv1a32<REX::Float64>;
	extern template struct Fnv1a32<REX::Float128>;
	extern template struct Fnv1a32<std::string>;
	extern template struct Fnv1a32<std::wstring>;
	extern template struct Fnv1a32<std::string_view>;
	extern template struct Fnv1a32<std::wstring_view>;
	extern template struct Fnv1a32<std::nullptr_t>;
	extern template struct Fnv1a32<void*>;
	extern template struct Fnv1a32<const void*>;

	extern template std::uint32_t HashFnv1a32(const bool&) noexcept;
	extern template std::uint32_t HashFnv1a32(const char&) noexcept;
	extern template std::uint32_t HashFnv1a32(const wchar_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const char8_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const char16_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const char32_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::int8_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::uint8_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::int16_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::uint16_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::int32_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::uint32_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::int64_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::uint64_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(const REX::Float32&) noexcept;
	extern template std::uint32_t HashFnv1a32(const REX::Float64&) noexcept;
	extern template std::uint32_t HashFnv1a32(const REX::Float128&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::string&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::wstring&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::string_view&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::wstring_view&) noexcept;
	extern template std::uint32_t HashFnv1a32(const std::nullptr_t&) noexcept;
	extern template std::uint32_t HashFnv1a32(void* const&) noexcept;
	extern template std::uint32_t HashFnv1a32(const void* const&) noexcept;

	template <class Key>
	struct Fnv1a64;

	template <class T>
	concept fnv1a64_hashable =
		std::is_invocable_r_v<
			std::uint64_t, Fnv1a64<std::decay_t<T>>, T>;

	template <class T>
	concept nothrow_fnv1a64_hashable =
		std::is_nothrow_invocable_r_v<
			std::uint64_t, Fnv1a64<std::decay_t<T>>, T>;

	template <class Key>
	struct Fnv1a64
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(Key a_data) const noexcept
			requires(std::is_arithmetic_v<Key> || std::is_enum_v<Key> || std::is_pointer_v<Key>)
		{
			const auto bytes = std::bit_cast<std::array<const std::byte, sizeof(Key)>>(a_data);
			return Impl::GenerateFnv1a64Hash(std::span<const std::byte>(bytes));
		}
	};

	template <>
	struct Fnv1a64<std::nullptr_t>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(std::nullptr_t) const noexcept
		{
			static constexpr auto HASH = std::invoke(Fnv1a64<std::uintptr_t>(), 0);
			return HASH;
		}
	};

	template <>
	struct Fnv1a64<std::basic_string<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(const std::basic_string<char>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a64Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Fnv1a64<std::basic_string<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint64_t operator()(const std::basic_string<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a64Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <>
	struct Fnv1a64<std::basic_string_view<char>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(const std::basic_string_view<char>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a64Hash(std::span<const char>(a_key));
		}
	};

	template <>
	struct Fnv1a64<std::basic_string_view<wchar_t>>
	{
	public:
		[[nodiscard]] std::uint64_t operator()(const std::basic_string_view<wchar_t>& a_key) const noexcept
		{
			return Impl::GenerateFnv1a64Hash(std::span<const char>(std::span{ reinterpret_cast<const char*>(a_key.data()), a_key.size() * sizeof(wchar_t) }));
		}
	};

	template <class T, std::size_t N>
	struct Fnv1a64<std::span<T, N>>
	{
	public:
		[[nodiscard]] constexpr std::uint64_t operator()(std::span<T, N> a_key) const noexcept
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
		[[nodiscard]] constexpr std::uint64_t operator()(const std::array<T, N>& a_key) const noexcept
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
	[[nodiscard]] constexpr std::uint64_t HashFnv1a64(const T& a_key) //
		noexcept(nothrow_fnv1a64_hashable<T>)
	{
		return std::invoke(Fnv1a64<std::decay_t<T>>(), a_key);
	}

	extern template struct Fnv1a64<bool>;
	extern template struct Fnv1a64<char>;
	extern template struct Fnv1a64<wchar_t>;
	extern template struct Fnv1a64<char8_t>;
	extern template struct Fnv1a64<char16_t>;
	extern template struct Fnv1a64<char32_t>;
	extern template struct Fnv1a64<std::int8_t>;
	extern template struct Fnv1a64<std::uint8_t>;
	extern template struct Fnv1a64<std::int16_t>;
	extern template struct Fnv1a64<std::uint16_t>;
	extern template struct Fnv1a64<std::int32_t>;
	extern template struct Fnv1a64<std::uint32_t>;
	extern template struct Fnv1a64<std::int64_t>;
	extern template struct Fnv1a64<std::uint64_t>;
	extern template struct Fnv1a64<REX::Float32>;
	extern template struct Fnv1a64<REX::Float64>;
	extern template struct Fnv1a64<REX::Float128>;
	extern template struct Fnv1a64<std::string>;
	extern template struct Fnv1a64<std::wstring>;
	extern template struct Fnv1a64<std::string_view>;
	extern template struct Fnv1a64<std::wstring_view>;
	extern template struct Fnv1a64<std::nullptr_t>;
	extern template struct Fnv1a64<void*>;
	extern template struct Fnv1a64<const void*>;

	extern template std::uint64_t HashFnv1a64(const bool&) noexcept;
	extern template std::uint64_t HashFnv1a64(const char&) noexcept;
	extern template std::uint64_t HashFnv1a64(const wchar_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const char8_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const char16_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const char32_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::int8_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::uint8_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::int16_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::uint16_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::int32_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::uint32_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::int64_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::uint64_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(const REX::Float32&) noexcept;
	extern template std::uint64_t HashFnv1a64(const REX::Float64&) noexcept;
	extern template std::uint64_t HashFnv1a64(const REX::Float128&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::string&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::wstring&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::string_view&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::wstring_view&) noexcept;
	extern template std::uint64_t HashFnv1a64(const std::nullptr_t&) noexcept;
	extern template std::uint64_t HashFnv1a64(void* const&) noexcept;
	extern template std::uint64_t HashFnv1a64(const void* const&) noexcept;
}
