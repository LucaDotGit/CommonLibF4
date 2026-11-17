#pragma once

#include "REX/StaticSortedSet.hpp"

namespace REX
{
	template <class Key, std::size_t N, class KeyCompare = std::less<Key>>
	using StaticSet = StaticSortedSet<Key, N, KeyCompare>;

	template <class... Args>
	[[nodiscard]]
	constexpr auto CreateStaticSet(Args&&... a_args)
		noexcept((std::is_nothrow_constructible_v<Args, std::common_type_t<Args...>> && ...))
			-> StaticSet<std::common_type_t<Args...>, sizeof...(Args)>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return StaticSet(std::array{static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))...});
	}

	template <template <class> class KeyCompare, class... Args>
	[[nodiscard]]
	constexpr auto CreateStaticSet(Args&&... a_args)
		noexcept((std::is_nothrow_constructible_v<Args, std::common_type_t<Args...>> && ...))
			-> StaticSet<std::common_type_t<Args...>, sizeof...(Args), KeyCompare<std::common_type_t<Args...>>>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return StaticSet(std::array{static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))...});
	}
}
