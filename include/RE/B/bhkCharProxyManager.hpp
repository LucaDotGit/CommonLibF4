#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkIWorldStepListener.hpp"

namespace RE
{
	class bhkCharProxyController;

	class __declspec(novtable) bhkCharProxyManager
		: public bhkIWorldStepListener // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkCharProxyManager };
		inline static constexpr auto VTABLE{ VTABLE::bhkCharProxyManager };

		class ThreadLocalCharRBDeferredCmds; // TODO

		~bhkCharProxyManager() override; // 00

		// members
		BSTArray<bhkCharProxyController*> proxyControllers;						 // 10
		BSTHashMap<bhkCharProxyController*, std::uint32_t> proxyControllerIndex; // 28
		BSTArray<ThreadLocalCharRBDeferredCmds> deferredCommands;				 // 58
	};
	static_assert(sizeof(bhkCharProxyManager) == 0x70);
}
