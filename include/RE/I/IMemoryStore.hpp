#pragma once

#include "RE/I/IMemoryStoreBase.hpp"

namespace RE
{
	class __declspec(novtable) IMemoryStore
		: public IMemoryStoreBase // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::IMemoryStore };
		inline static constexpr auto VTABLE{ VTABLE::IMemoryStore };

		~IMemoryStore() override = default; // 00

		// add
		virtual void* AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) = 0; // 04
		virtual void DeallocateAlignImpl(void*& a_block) = 0;								// 05
		virtual void* TryAllocateImpl(std::size_t a_size, std::uint32_t a_alignment);		// 06 - { return nullptr; }
	};
	static_assert(sizeof(IMemoryStore) == 0x08);
}
