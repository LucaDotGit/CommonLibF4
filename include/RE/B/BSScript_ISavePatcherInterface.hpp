#pragma once

namespace RE::BSScript
{
	class IVirtualMachine;
	class StackFrame;

	class __declspec(novtable) ISavePatcherInterface
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__ISavePatcherInterface };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__ISavePatcherInterface };

		virtual ~ISavePatcherInterface() = default; // 00

		// add
		virtual void PatchStackFrame(StackFrame& a_stackFrame, IVirtualMachine& a_vm) = 0; // 01
	};
	static_assert(sizeof(ISavePatcherInterface) == 0x08);
}
