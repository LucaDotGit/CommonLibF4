#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkIWorldStepListener.hpp"

namespace RE
{
	class bhkCharRigidBodyController;

	class __declspec(novtable) bhkCharRigidBodyManager
		: public bhkIWorldStepListener // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::bhkCharRigidBodyManager };
		inline static constexpr auto VTABLE{ VTABLE::bhkCharRigidBodyManager };

		class ThreadLocalCharRBDeferredCmds; // TODO

		~bhkCharRigidBodyManager() override; // 00

		// members
		BSTArray<bhkCharRigidBodyController*> rigidBodyControllers;						 // 10
		BSTHashMap<bhkCharRigidBodyController*, std::uint32_t> rigidBodyControllerIndex; // 28
		BSTArray<ThreadLocalCharRBDeferredCmds> deferredCommands;						 // 58
	};
	static_assert(sizeof(bhkCharRigidBodyManager) == 0x70);
}
