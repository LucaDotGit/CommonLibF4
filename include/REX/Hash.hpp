#pragma once

#include "REX/Concepts.hpp"
#include "REX/Locale.hpp"

namespace REX::Impl
{
	// Source: https://stackoverflow.com/questions/2590677/how-do-i-combine-hash-values-in-c0x
	template <REX::hashable T>
	void HashCombine(std::size_t& a_hash, T&& a_key) //
		noexcept(nothrow_hashable<T>)
	{
		constexpr auto HASH_SEED = static_cast<std::size_t>(0x9E3779B9);
		a_hash ^= std::invoke(std::hash<std::decay_t<T>>(), std::forward<T>(a_key)) + HASH_SEED + (a_hash << 6) + (a_hash >> 2);
	}
}

namespace REX
{
	template <hashable T>
	[[nodiscard]] std::size_t Hash(const T& a_key) //
		noexcept(nothrow_hashable<T>)
	{
		return std::invoke(std::hash<std::decay_t<T>>(), a_key);
	}

	extern template std::size_t Hash(const bool&) noexcept;
	extern template std::size_t Hash(const char&) noexcept;
	extern template std::size_t Hash(const wchar_t&) noexcept;
	extern template std::size_t Hash(const char8_t&) noexcept;
	extern template std::size_t Hash(const char16_t&) noexcept;
	extern template std::size_t Hash(const char32_t&) noexcept;
	extern template std::size_t Hash(const std::int8_t&) noexcept;
	extern template std::size_t Hash(const std::uint8_t&) noexcept;
	extern template std::size_t Hash(const std::int16_t&) noexcept;
	extern template std::size_t Hash(const std::uint16_t&) noexcept;
	extern template std::size_t Hash(const std::int32_t&) noexcept;
	extern template std::size_t Hash(const std::uint32_t&) noexcept;
	extern template std::size_t Hash(const std::int64_t&) noexcept;
	extern template std::size_t Hash(const std::uint64_t&) noexcept;
	extern template std::size_t Hash(const REX::Float32&) noexcept;
	extern template std::size_t Hash(const REX::Float64&) noexcept;
	extern template std::size_t Hash(const REX::Float128&) noexcept;
	extern template std::size_t Hash(const std::string&) noexcept;
	extern template std::size_t Hash(const std::wstring&) noexcept;
	extern template std::size_t Hash(const std::string_view&) noexcept;
	extern template std::size_t Hash(const std::wstring_view&) noexcept;
	extern template std::size_t Hash(const std::nullptr_t&) noexcept;
	extern template std::size_t Hash(void* const&) noexcept;
	extern template std::size_t Hash(const void* const&) noexcept;

	template <class... Args>
	[[nodiscard]] std::size_t HashCombine(Args&&... a_args) //
		noexcept((nothrow_hashable<Args> && ...))
		requires((hashable<Args> && ...) && sizeof...(Args) >= 2)
	{
		auto hash = static_cast<std::size_t>(0);
		(Impl::HashCombine(hash, std::forward<Args>(a_args)), ...);
		return hash;
	}

	template <std::forward_iterator It>
	[[nodiscard]] std::size_t HashRange(It a_begin, It a_end) //
		noexcept(nothrow_hashable<typename std::iterator_traits<It>::value_type>)
		requires(hashable<typename std::iterator_traits<It>::value_type>)
	{
		auto hash = static_cast<std::size_t>(0);
		for (auto it = a_begin; it != a_end; it++) {
			Impl::HashCombine(hash, *it);
		}

		return hash;
	}

	template <std::ranges::forward_range T>
	[[nodiscard]] std::size_t HashRange(const T& a_range) //
		noexcept(nothrow_hashable<std::ranges::range_value_t<T>>)
		requires(hashable<std::ranges::range_value_t<T>>)
	{
		const auto begin = std::ranges::begin(a_range);
		const auto end = std::ranges::end(a_range);

		auto hash = static_cast<std::size_t>(0);
		for (auto it = begin; it != end; it++) {
			Impl::HashCombine(hash, *it);
		}

		return hash;
	}

	// Source: http://www.cse.yorku.ca/~oz/hash.html#sdbm
	template <class T>
	[[nodiscard]] constexpr std::size_t HashIgnoreCase(std::basic_string_view<T> a_key) noexcept
	{
		auto hash = static_cast<std::size_t>(0);
		for (const auto character : a_key) {
			const auto lowerChar = REX::ToLower(character);
			hash = lowerChar + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}

	extern template std::size_t HashIgnoreCase(std::string_view a_key) noexcept;
	extern template std::size_t HashIgnoreCase(std::wstring_view a_key) noexcept;
}
