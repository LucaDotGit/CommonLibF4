#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkIWorldStepListener.hpp"

namespace RE
{
	class bhkCharProxyController;

	class __declspec(novtable) bhkCharProxyManager : public bhkIWorldStepListener // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkCharProxyManager;
		inline static constexpr const auto& VTABLE = VTABLE::bhkCharProxyManager;

		class ThreadLocalCharRBDeferredCmds; // To-Do

		~bhkCharProxyManager() override; // 0x00

		// members
		BSTArray<bhkCharProxyController*> proxyControllers;						 // 0x10
		BSTHashMap<bhkCharProxyController*, std::uint32_t> proxyControllerIndex; // 0x28
		BSTArray<ThreadLocalCharRBDeferredCmds> deferredCommands;				 // 0x58
	};

	static_assert(sizeof(bhkCharProxyManager) == 0x70);
}
