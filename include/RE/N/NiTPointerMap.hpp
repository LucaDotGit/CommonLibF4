#pragma once

#include "RE/N/NiTMap.hpp"
#include "RE/N/NiTPointerAllocator.hpp"

namespace RE
{
	template <class Key, class T>
	class NiTPointerMap
		: public NiTMapBase<NiTPointerAllocator<std::size_t>, Key, T> // 00
	{
	private:
		using super = NiTMapBase<NiTPointerAllocator<std::size_t>, Key, T>;

	public:
		using key_type = super::key_type;
		using mapped_type = super::mapped_type;
		using value_type = super::value_type;
		using size_type = super::size_type;
		using allocator_type = super::allocator_type;

	protected:
		value_type* malloc_value() override;		   // 05
		void free_value(value_type* a_value) override; // 06
	};
	static_assert(sizeof(NiTPointerMap<void*, void*>) == 0x20);
}
