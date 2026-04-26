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
		BSTCommonScrapHeapMessageQueue<BSPackedTask> queue; // 00
		UnpackFuncType* unpackFunc{ nullptr };				// 28
	};
	static_assert(sizeof(BSPackedTaskQueue) == 0x30);
}
