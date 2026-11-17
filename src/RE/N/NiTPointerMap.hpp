#pragma once

#include "RE/N/NiTMap.hpp"
#include "RE/N/NiTPointerAllocator.hpp"

namespace RE
{
	template <class Key, class T>
	class NiTPointerMap : public NiTMapBase<Key, T, NiTPointerAllocator<std::size_t>> // 0x00
	{
	private:
		using super = NiTMapBase<Key, T, NiTPointerAllocator<std::size_t>>;

	public:
		using key_type = super::key_type;
		using mapped_type = super::mapped_type;
		using value_type = super::value_type;
		using size_type = super::size_type;
		using allocator_type = super::allocator_type;

	protected:
		auto malloc_value() -> value_type* override;   // 0x05
		void free_value(value_type* a_value) override; // 0x06
	};

	static_assert(sizeof(NiTPointerMap<void*, void*>) == 0x20);
}
