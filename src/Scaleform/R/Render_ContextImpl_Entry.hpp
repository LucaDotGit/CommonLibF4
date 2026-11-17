#pragma once

#include "Scaleform/L/List.hpp"

namespace Scaleform::Render::ContextImpl
{
	class EntryChange;
	class EntryData;
	class TreeCacheNode;

	class Entry
	{
	public:
		class PropagateNode : public ListNode<PropagateNode> // 0x00
		{
		public:
		};

		static_assert(sizeof(PropagateNode) == 0x10);

		// members
		union
		{
		public:
			Entry* prev{nullptr};
			EntryChange* change;
		}; // 0x00

		union
		{
		public:
			Entry* next{nullptr};
			std::size_t refCount;
		}; // 0x08

		EntryData* native{nullptr};		  // 0x10
		TreeCacheNode* renderer{nullptr}; // 0x18
		Entry* parent{nullptr};			  // 0x20
		PropagateNode node;				  // 0x28
	};

	static_assert(sizeof(Entry) == 0x38);
}
