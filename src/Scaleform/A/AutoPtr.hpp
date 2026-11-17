#pragma once

namespace Scaleform
{
	template <class T>
	class AutoPtr
	{
	public:
		// members
		T* object;	// 0x00
		bool owner; // 0x08
	};

	static_assert(sizeof(AutoPtr<void*>) == 0x10);
}
