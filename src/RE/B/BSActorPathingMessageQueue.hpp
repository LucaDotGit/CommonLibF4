#pragma once

#include "RE/B/BSActorPathingMessage.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"

namespace RE
{
	class BSActorPathingMessageQueue : public BSIntrusiveRefCounted // 0x00
	{
	public:
		// members
		BSTSmallArray<BSActorPathingMessage, 1> messages; // 0x08
		mutable BSSpinLock messagesLock;				  // 0x30
	};

	static_assert(sizeof(BSActorPathingMessageQueue) == 0x38);
}
