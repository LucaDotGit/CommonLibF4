#pragma once

#include "RE/H/hkInplaceArray.hpp"

namespace RE
{
	class hkVisualDebugger;

	class __declspec(novtable) hkProcessContext
	{
	public:
		virtual ~hkProcessContext(); // 00

		// add
		virtual const char* GetType() = 0;				  // 01
		virtual void SetOwner(hkVisualDebugger* a_owner); // 02 - { owner = a_owner; }

		// members
		hkVisualDebugger* owner{ nullptr };					  // 08
		hkInplaceArray<const char*, 6> monitorStreamBegins{}; // 10
		hkInplaceArray<const char*, 6> monitorStreamEnds{};	  // 50
	};
	static_assert(sizeof(hkProcessContext) == 0x90);
}
