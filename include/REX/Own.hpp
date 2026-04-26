#pragma once

namespace REX
{
	template <class T>
		requires(std::is_pointer_v<T>)
	using Owner = T;

	template <class T>
		requires(std::is_pointer_v<T>)
	using Observer = T;
}
