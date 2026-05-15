#pragma once

namespace RE
{
	class hkClass;

	class hkVisualDebuggerTrackedObject
	{
	public:
		// members
		void* ptr;		   // 00
		hkClass* clss;	   // 08
		std::uint64_t tag; // 10
	};
	static_assert(sizeof(hkVisualDebuggerTrackedObject) == 0x18);
}
