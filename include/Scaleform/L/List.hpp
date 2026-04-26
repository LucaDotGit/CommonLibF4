#pragma once

namespace Scaleform
{
	template <class T>
	class ListNode
	{
	public:
		// members
		T* prev{ nullptr }; // 00
		T* next{ nullptr }; // 08
	};
	static_assert(sizeof(ListNode<std::any>) == 0x10);

	template <class T, class B = T>
	class List
	{
	public:
		// members
		ListNode<B> root; // 00
	};
	static_assert(sizeof(List<std::any>) == 0x10);

	template <class T, class Accessor>
	class List2
	{
	public:
		// members
		T root; // 00
	};
	static_assert(sizeof(List2<std::any, std::any>) == sizeof(std::any));
}
