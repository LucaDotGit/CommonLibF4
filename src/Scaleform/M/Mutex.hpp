#pragma once

#include "Scaleform/A/AcquireInterface.hpp"
#include "Scaleform/W/Waitable.hpp"

namespace Scaleform
{
	class MutexImpl;

	class __declspec(novtable) Mutex :
		public Waitable,		// 0x00
		public AcquireInterface // 0x18
	{
	public:
		// members
		MutexImpl* impl; // 0x20
	};

	static_assert(sizeof(Mutex) == 0x28);
}
