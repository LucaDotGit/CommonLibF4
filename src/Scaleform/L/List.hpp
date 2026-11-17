#pragma once

namespace Scaleform
{
	template <class T>
	class ListNode
	{
	public:
		// members
		T* prev{nullptr}; // 0x00
		T* next{nullptr}; // 0x08
	};

	static_assert(sizeof(ListNode<std::any>) == 0x10);

	template <class T, class B = T>
	class List
	{
	public:
		// members
		ListNode<B> root; // 0x00
	};

	static_assert(sizeof(List<std::any>) == 0x10);

	template <class T, class Accessor>
	class List2
	{
	public:
		// members
		T root; // 0x00
	};

	static_assert(sizeof(List2<std::any, std::any>) == sizeof(std::any));
}
