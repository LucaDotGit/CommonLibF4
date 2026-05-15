#pragma once

#include "REX/StaticSortedMap.hpp"

namespace REX
{
	template <class Key, class T, std::size_t N, class KeyCompare = std::less<Key>>
	using StaticMap = StaticSortedMap<Key, T, N, KeyCompare>;

	template <class... Args>
	[[nodiscard]] constexpr auto make_static_map(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticMap<typename std::common_type_t<Args...>::first_type, typename std::common_type_t<Args...>::second_type, sizeof...(Args)>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}

	template <template <class> class KeyCompare, class... Args>
	[[nodiscard]] constexpr auto make_static_map(Args&&... a_args) //
		noexcept((std::is_nothrow_convertible_v<std::common_type_t<Args...>, Args> && ...))
			-> StaticMap<typename std::common_type_t<Args...>::first_type, typename std::common_type_t<Args...>::second_type, sizeof...(Args), KeyCompare<typename std::common_type_t<Args...>::first_type>>
		requires(sizeof...(Args) > 0 && (std::is_convertible_v<Args, std::common_type_t<Args...>> && ...))
	{
		return { static_cast<std::common_type_t<Args...>>(std::forward<Args>(a_args))... };
	}
}
