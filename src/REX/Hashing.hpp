#pragma once

#include "REX/Concepts.hpp"
#include "REX/Localization.hpp"

namespace REX::Impl
{
	// Source: https://stackoverflow.com/a/2595226
	template <REX::hashable T>
	void HashCombine(std::size_t& a_hash, T&& a_key) noexcept(nothrow_hashable<T>)
	{
		constexpr auto HASH_SEED = static_cast<std::size_t>(0x9E37'79B9);
		a_hash ^= std::invoke(std::hash<std::decay_t<T>>(), std::forward<T>(a_key)) +
				  HASH_SEED +
				  (a_hash << 6) +
				  (a_hash >> 2);
	}
}

namespace REX
{
	template <hashable T>
	[[nodiscard]]
	auto Hash(const T& a_key) noexcept(nothrow_hashable<T>) -> std::size_t
	{
		return std::invoke(std::hash<std::decay_t<T>>(), a_key);
	}

	template <class... Args>
	[[nodiscard]]
	auto HashCombine(Args&&... a_args) noexcept((nothrow_hashable<Args> && ...)) -> std::size_t
		requires((hashable<Args> && ...) && sizeof...(Args) >= 2)
	{
		auto hash = static_cast<std::size_t>(0);
		(Impl::HashCombine(hash, std::forward<Args>(a_args)), ...);
		return hash;
	}

	template <std::forward_iterator It>
	[[nodiscard]]
	auto HashRange(It a_begin, It a_end) noexcept(nothrow_hashable<typename std::iterator_traits<It>::value_type>)
		-> std::size_t
		requires(hashable<typename std::iterator_traits<It>::value_type>)
	{
		auto hash = static_cast<std::size_t>(0);
		for (auto it = a_begin; it != a_end; it++) {
			Impl::HashCombine(hash, *it);
		}

		return hash;
	}

	template <std::ranges::forward_range T>
	[[nodiscard]]
	auto HashRange(const T& a_range) noexcept(nothrow_hashable<std::ranges::range_value_t<T>>) -> std::size_t
		requires(hashable<std::ranges::range_value_t<T>>)
	{
		return HashRange(std::ranges::begin(a_range), std::ranges::end(a_range));
	}

	// Source: http://cse.yorku.ca/~oz/hash.html#sdbm
	template <class T>
	[[nodiscard]]
	constexpr auto HashIgnoreCase(std::basic_string_view<T> a_key) noexcept -> std::size_t
	{
		auto hash = static_cast<std::size_t>(0);
		for (const auto character : a_key) {
			const auto lowerChar = REX::ToLower(character);
			hash = static_cast<std::size_t>(lowerChar) + (hash << 6) + (hash << 16) - hash;
		}

		return hash;
	}

	static_assert(HashIgnoreCase("Hello"sv) == 0x66EB'1BB3'28D1'9932);

	template <REX::character CharT>
	struct StringHash
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_key) const noexcept -> std::size_t
		{
			return REX::Hash(a_key);
		}
	};

	template <REX::character CharT>
	struct StringHashIgnoreCase
	{
	public:
		using is_transparent = void;

		[[nodiscard]]
		constexpr auto operator()(std::basic_string_view<CharT> a_key) const noexcept -> std::size_t
		{
			return REX::HashIgnoreCase(a_key);
		}
	};
}
