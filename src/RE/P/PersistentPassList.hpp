#pragma once

namespace RE
{
	class BSRenderPass;

	class PersistentPassList
	{
	public:
		// members
		BSRenderPass* head; // 0x00
		BSRenderPass* tail; // 0x08
	};

	static_assert(sizeof(PersistentPassList) == 0x10);
}
