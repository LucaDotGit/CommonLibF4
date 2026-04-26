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
		virtual ~BSTMessageQueue() = default; // 00

		// add
		virtual bool Push(const T& a_message) = 0;	  // 01
		virtual bool TryPush(const T& a_message) = 0; // 02
		virtual bool Pop(T& a_message) = 0;			  // 03
		virtual bool TryPop(T& a_message) = 0;		  // 04
	};
	static_assert(sizeof(BSTMessageQueue<std::any>) == 0x08);

	template <class T>
	class __declspec(novtable) BSTCommonMessageQueue
		: public BSTMessageQueue<T> // 00
	{
	public:
		// override (BSTMessageQueue<T>)
		bool Push(const T& a_message) override;	   // 01
		bool TryPush(const T& a_message) override; // 02
		bool Pop(T& a_message) override;		   // 03
		bool TryPop(T& a_message) override;		   // 04

		// add
		virtual bool DoTryPush(const T& a_message); // 05 - { return false; }
		virtual bool DoTryPop(T& a_message);		// 06 - { return false; }

		// members
		volatile std::uint32_t lock{ 0 }; // 08
	};
	static_assert(sizeof(BSTCommonMessageQueue<std::any>) == 0x10);

	template <class T>
	class __declspec(novtable) BSTCommonLLMessageQueue
		: public BSTCommonMessageQueue<T> // 00
	{
	public:
		// members
		BSTFreeList<T>* freeList{ nullptr };  // 10
		BSTFreeListElem<T>* head{ nullptr };  // 18
		BSTFreeListElem<T>** tail{ nullptr }; // 20
	};
	static_assert(sizeof(BSTCommonLLMessageQueue<std::any>) == 0x28);

	template <class T>
	class __declspec(novtable) BSTCommonScrapHeapMessageQueue
		: public BSTCommonMessageQueue<T>
	{
	public:
		// override (BSTMessageQueue<T>)
		bool DoTryPush(const T& a_message) override; // 05
		bool DoTryPop(T& a_message) override;		 // 06

		// members
		ScrapHeap* scrapHeap{ nullptr };		   // 10
		BSScrapHeapQueueElem<T>* head{ nullptr };  // 18
		BSScrapHeapQueueElem<T>** tail{ nullptr }; // 20
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
			std::array<T*, Size> data;						// 00
			alignas(0x80) volatile std::uint32_t start;		// ??
			alignas(0x80) volatile std::uint32_t fetched;	// ??
			alignas(0x80) volatile std::uint32_t end;		// ??
			alignas(0x80) volatile std::uint32_t allocated; // ??
		};
		static_assert(sizeof(PtrMultiProdCons<void*, 128, 0>) == 0x600);

		template <class QueueContainer, class T, std::uint32_t Size, std::uint32_t Unknown>
		class ObjQueueBase
		{
		public:
			// members
			std::array<T, Size> data;			 // 00
			alignas(0x80) QueueContainer queued; // ??
			alignas(0x80) QueueContainer free;	 // ??
		};
		static_assert(sizeof(ObjQueueBase<PtrMultiProdCons<void*, 128, 0>, void*, 64, 0>) == 0xE00);

		template <class T, std::uint32_t Size, std::uint32_t Unknown>
		class ObjMultiProdCons
			: public ObjQueueBase<PtrMultiProdCons<T, Size * 2, Unknown>, T, Size, Unknown> // 00
		{
		};
		static_assert(sizeof(ObjMultiProdCons<void*, 64, 0>) == 0xE00);
	};

	template <class T, std::size_t Size>
	class __declspec(novtable) BSTCommonStaticMessageQueue
		: public BSTMessageQueue<T> // 00
	{
	public:
		~BSTCommonStaticMessageQueue() override; // 00

		// override (BSTMessageQueue<T>)
		bool Push(const T& a_message) override;	   // 01
		bool TryPush(const T& a_message) override; // 02
		bool Pop(T& a_message) override;		   // 03
		bool TryPop(T& a_message) override;		   // 04

		// members
		alignas(0x80) std::array<char, sizeof(T) * Size> queueBuffer; // 10
		BSTLocklessQueue::ObjMultiProdCons<T, 128, 0>* locklessQueue; // ??
	};
}
