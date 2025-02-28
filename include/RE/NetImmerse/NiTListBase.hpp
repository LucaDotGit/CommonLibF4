#pragma once

namespace RE
{
	template <class T>
	class NiTListItem
	{
	public:
		NiTListItem* next; // 00
		NiTListItem* prev; // 08
		T element;		   // 10
	};

	template <class Allocator, class T>
	class NiTListBase
	{
	public:
		struct AntiBloatAllocator
			: public Allocator
		{
		public:
			// members
			std::uint32_t size; // ??
		};

		// members
		NiTListItem<T>* head;		  // 00
		NiTListItem<T>* tail;		  // 08
		AntiBloatAllocator allocator; // 10
	};
}
