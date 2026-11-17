#pragma once

#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/bhkIWorldStepListener.hpp"

namespace RE
{
	class bhkCharRigidBodyController;

	class __declspec(novtable) bhkCharRigidBodyManager : public bhkIWorldStepListener // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::bhkCharRigidBodyManager;
		inline static constexpr const auto& VTABLE = VTABLE::bhkCharRigidBodyManager;

		class ThreadLocalCharRBDeferredCmds; // To-Do

		~bhkCharRigidBodyManager() override; // 0x00

		// members
		BSTArray<bhkCharRigidBodyController*> rigidBodyControllers;						 // 0x10
		BSTHashMap<bhkCharRigidBodyController*, std::uint32_t> rigidBodyControllerIndex; // 0x28
		BSTArray<ThreadLocalCharRBDeferredCmds> deferredCommands;						 // 0x58
	};

	static_assert(sizeof(bhkCharRigidBodyManager) == 0x70);
}
