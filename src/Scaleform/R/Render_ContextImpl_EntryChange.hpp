#pragma once

namespace Scaleform::Render::ContextImpl
{
	class Entry;

	class EntryChange
	{
	public:
		// members
		Entry* node; // 0x00

		union
		{
		public:
			std::uint32_t changeBits;
			EntryChange* nextFreeNode;
		}; // 0x08
	};

	static_assert(sizeof(EntryChange) == 0x10);
}
