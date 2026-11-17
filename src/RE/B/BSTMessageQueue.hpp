#pragma once

#include "RE/B/BSTFreeList.hpp"

namespace RE
{
	class ScrapHeap;

	template <class T>
	class BSScrapHeapQueueElem;

	template <class T>
	class __declspec(novtable) BSTMessageQueue
	{
	public:
		virtual ~BSTMessageQueue() = default; // 0x00

		// add
		virtual auto Push(const T& a_message) -> bool = 0;	  // 0x01
		virtual auto TryPush(const T& a_message) -> bool = 0; // 0x02
		virtual auto Pop(T& a_message) -> bool = 0;			  // 0x03
		virtual auto TryPop(T& a_message) -> bool = 0;		  // 0x04
	};

	static_assert(sizeof(BSTMessageQueue<std::any>) == 0x08);

	template <class T>
	class __declspec(novtable) BSTCommonMessageQueue : public BSTMessageQueue<T> // 0x00
	{
	public:
		~BSTCommonMessageQueue() override; // 0x00

		// override (BSTMessageQueue<T>)
		auto Push(const T& a_message) -> bool override;	   // 0x01
		auto TryPush(const T& a_message) -> bool override; // 0x02
		auto Pop(T& a_message) -> bool override;		   // 0x03
		auto TryPop(T& a_message) -> bool override;		   // 0x04

		// add
		virtual auto DoTryPush(const T& a_message) -> bool; // 0x05 - { return false; }
		virtual auto DoTryPop(T& a_message) -> bool;		// 0x06 - { return false; }

		// members
		volatile std::uint32_t lock{0}; // 0x08
	};

	static_assert(sizeof(BSTCommonMessageQueue<std::any>) == 0x10);

	template <class T>
	class __declspec(novtable) BSTCommonLLMessageQueue : public BSTCommonMessageQueue<T> // 0x00
	{
	public:
		~BSTCommonLLMessageQueue() override; // 0x00

		// members
		BSTFreeList<T>* freeList{nullptr};	// 0x10
		BSTFreeListElem<T>* head{nullptr};	// 0x18
		BSTFreeListElem<T>** tail{nullptr}; // 0x20
	};

	static_assert(sizeof(BSTCommonLLMessageQueue<std::any>) == 0x28);

	template <class T>
	class __declspec(novtable) BSTCommonScrapHeapMessageQueue : public BSTCommonMessageQueue<T>
	{
	public:
		~BSTCommonScrapHeapMessageQueue() override; // 0x00

		// override (BSTMessageQueue<T>)
		auto DoTryPush(const T& a_message) -> bool override; // 0x05
		auto DoTryPop(T& a_message) -> bool override;		 // 0x06

		// members
		ScrapHeap* scrapHeap{nullptr};			 // 0x10
		BSScrapHeapQueueElem<T>* head{nullptr};	 // 0x18
		BSScrapHeapQueueElem<T>** tail{nullptr}; // 0x20
	};

	static_assert(sizeof(BSTCommonScrapHeapMessageQueue<std::any>) == 0x28);

	class BSTLocklessQueue
	{
	public:
		template <class T, std::uint32_t Size, std::uint32_t Unknown>
		class PtrMultiProdCons
		{
		public:
			// members
			std::array<T*, Size> data;						// 0x00
			alignas(0x80) volatile std::uint32_t start;		// 0x??
			alignas(0x80) volatile std::uint32_t fetched;	// 0x??
			alignas(0x80) volatile std::uint32_t end;		// 0x??
			alignas(0x80) volatile std::uint32_t allocated; // 0x??
		};

		static_assert(sizeof(PtrMultiProdCons<void*, 128, 0>) == 0x600);

		template <class QueueContainer, class T, std::uint32_t Size, std::uint32_t Unknown>
		class ObjQueueBase
		{
		public:
			// members
			std::array<T, Size> data;			 // 0x00
			alignas(0x80) QueueContainer queued; // 0x??
			alignas(0x80) QueueContainer free;	 // 0x??
		};

		static_assert(sizeof(ObjQueueBase<PtrMultiProdCons<void*, 128, 0>, void*, 64, 0>) == 0xE00);

		template <class T, std::uint32_t Size, std::uint32_t Unknown>
		class ObjMultiProdCons : public ObjQueueBase<PtrMultiProdCons<T, Size * 2, Unknown>, T, Size, Unknown> // 0x00
		{
		};

		static_assert(sizeof(ObjMultiProdCons<void*, 64, 0>) == 0xE00);
	};

	template <class T, std::size_t Size>
	class __declspec(novtable) BSTCommonStaticMessageQueue : public BSTMessageQueue<T> // 0x00
	{
	public:
		~BSTCommonStaticMessageQueue() override; // 0x00

		// override (BSTMessageQueue<T>)
		auto Push(const T& a_message) -> bool override;	   // 0x01
		auto TryPush(const T& a_message) -> bool override; // 0x02
		auto Pop(T& a_message) -> bool override;		   // 0x03
		auto TryPop(T& a_message) -> bool override;		   // 0x04

		// members
		alignas(0x80) REX::StaticString<sizeof(T) * Size> queueBuffer; // 0x10
		BSTLocklessQueue::ObjMultiProdCons<T, 128, 0>* locklessQueue;  // 0x??
	};
}
