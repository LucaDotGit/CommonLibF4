#pragma once

#include "RE/Bethesda/BSScript/IVirtualMachine.hpp"
#include "RE/Bethesda/BSScript/StackFrame.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
	class StackFrame;

	class ISavePatcherInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ISavePatcherInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ISavePatcherInterface };

		virtual ~ISavePatcherInterface() = default; // 00

		// add
		virtual void PatchStackFrame(StackFrame&, IVirtualMachine&) = 0; // 01
	};
	static_assert(sizeof(ISavePatcherInterface) == 0x8);
}
