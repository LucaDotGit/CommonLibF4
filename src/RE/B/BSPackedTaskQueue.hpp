#pragma once

#include "RE/B/BSTMessageQueue.hpp"

namespace RE
{
	class BSPackedTask;

	class BSPackedTaskQueue
	{
	public:
		using UnpackFuncType = void (*)(const BSPackedTask&);

		// members
		BSTCommonScrapHeapMessageQueue<BSPackedTask> queue; // 0x00
		UnpackFuncType* unpackFunc{nullptr};				// 0x28
	};

	static_assert(sizeof(BSPackedTaskQueue) == 0x30);
}
