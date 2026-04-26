#pragma once

#include "RE/N/NiMemManager.hpp"

namespace RE
{
	template <class T>
	class DFALL
	{
	public:
		using value_type = T;

		[[nodiscard]] value_type* Allocate() noexcept
		{
			return ni_malloc<value_type>();
		}

		void Deallocate(value_type* a_ptr) noexcept
		{
			ni_free(a_ptr);
		}
	};

	template <class T>
	using NiTDefaultAllocator = DFALL<T>;
}
