#pragma once

#include "RE/H/hkInplaceArray.hpp"

namespace RE
{
	class hkVisualDebugger;

	class __declspec(novtable) hkProcessContext
	{
	public:
		virtual ~hkProcessContext(); // 0x00

		// add
		virtual auto GetType() -> const char* = 0;		  // 0x01
		virtual void SetOwner(hkVisualDebugger* a_owner); // 0x02 - { owner = a_owner; }

		// members
		hkVisualDebugger* owner{nullptr};					  // 0x08
		hkInplaceArray<const char*, 6> monitorStreamBegins{}; // 0x10
		hkInplaceArray<const char*, 6> monitorStreamEnds{};	  // 0x50
	};

	static_assert(sizeof(hkProcessContext) == 0x90);
}
