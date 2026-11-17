#pragma once

#include "RE/B/BSScript_ISavePatcherInterface.hpp"

namespace RE::BSScript
{
	class IVirtualMachine;
	class StackFrame;
}

namespace RE::GameScript
{
	class __declspec(novtable) SavePatcher : public BSScript::ISavePatcherInterface // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameScript__SavePatcher;
		inline static constexpr const auto& VTABLE = VTABLE::GameScript__SavePatcher;

		~SavePatcher() override; // 0x00

		// override (BSScript::ISavePatcherInterface)
		void PatchStackFrame(BSScript::StackFrame& a_stackFrame, BSScript::IVirtualMachine& a_vm)
			override; // 0x01 - { return; }
	};

	static_assert(sizeof(SavePatcher) == 0x08);
}
