#pragma once

#include "RE/M/MemoryManager.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
	class StackFrame;

	class __declspec(novtable) ISavePatcherInterface
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__ISavePatcherInterface;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__ISavePatcherInterface;

		virtual ~ISavePatcherInterface() = default; // 0x00

		// add
		virtual void PatchStackFrame(StackFrame& a_stackFrame, IVirtualMachine& a_vm) = 0; // 0x01

		GAME_HEAP_REDEFINE_NEW(ISavePatcherInterface);
	};

	static_assert(sizeof(ISavePatcherInterface) == 0x08);
}
