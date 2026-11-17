#pragma once

#include "Scaleform/A/AcquireInterface.hpp"
#include "Scaleform/M/Mutex.hpp"
#include "Scaleform/W/WaitCondition.hpp"
#include "Scaleform/W/Waitable.hpp"

namespace Scaleform
{
	class __declspec(novtable) Event :
		public Waitable,		// 0x00
		public AcquireInterface // 0x18
	{
	public:
		// members
		volatile bool state;			  // 0x20
		volatile bool temporary;		  // 0x21
		mutable Mutex stateMutex;		  // 0x28
		WaitCondition stateWaitCondition; // 0x50
	};

	static_assert(sizeof(Event) == 0x58);
}
