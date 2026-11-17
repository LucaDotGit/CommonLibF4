#pragma once

#include "RE/I/IMemoryStoreBase.hpp"

namespace RE
{
	class __declspec(novtable) IMemoryStore : public IMemoryStoreBase // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::IMemoryStore;
		inline static constexpr const auto& VTABLE = VTABLE::IMemoryStore;

		~IMemoryStore() override = default; // 0x00

		// add
		virtual auto AllocateAlignImpl(std::size_t a_size, std::uint32_t a_alignment) -> void* = 0; // 0x04
		virtual void DeallocateAlignImpl(void*& a_block) = 0;										// 0x05
		virtual auto TryAllocateImpl(std::size_t a_size, std::uint32_t a_alignment)
			-> void*; // 0x06 - { return nullptr; }
	};

	static_assert(sizeof(IMemoryStore) == 0x08);
}
