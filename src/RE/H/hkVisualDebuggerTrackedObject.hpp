#pragma once

namespace RE
{
	class hkClass;

	class hkVisualDebuggerTrackedObject
	{
	public:
		// members
		void* ptr;		   // 0x00
		hkClass* clss;	   // 0x08
		std::uint64_t tag; // 0x10
	};

	static_assert(sizeof(hkVisualDebuggerTrackedObject) == 0x18);
}
