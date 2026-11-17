#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE
{
	template <class T>
	class BSTFreeListElem
	{
	public:
		// members
		std::array<std::byte, sizeof(T)> rawElem; // 0x00
		BSTFreeListElem<T>* next{nullptr};		  // 0x??
	};

	static_assert(sizeof(BSTFreeListElem<void*>) == 0x10);

	template <class T>
	class __declspec(novtable) BSTFreeList
	{
	public:
		virtual ~BSTFreeList(); // 0x00

		GAME_HEAP_REDEFINE_NEW(BSTFreeList);

		// members
		std::uint32_t lock{0};			   // 0x08
		BSTFreeListElem<T>* free{nullptr}; // 0x10
	};

	static_assert(sizeof(BSTFreeList<std::any>) == 0x18);

	template <class T, std::uint32_t N>
	class __declspec(novtable) BSTStaticFreeList : public BSTFreeList<T> // 0x00
	{
	public:
		inline static constexpr auto MAX_SIZE = N;

		~BSTStaticFreeList() override; // 0x00

		// members
		std::array<BSTFreeListElem<T>, MAX_SIZE> elements; // 0x??
	};

	static_assert(sizeof(BSTStaticFreeList<void*, 4>) == 0x58);
}
