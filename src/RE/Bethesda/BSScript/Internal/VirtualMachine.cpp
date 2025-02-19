#include "RE/Bethesda/BSScript/Internal/VirtualMachine.hpp"

#include "RE/Bethesda/GameScript.hpp"

namespace RE::BSScript::Internal
{
	VirtualMachine* VirtualMachine::GetSingleton()
	{
		auto vm = GameVM::GetSingleton();
		return vm ? static_cast<VirtualMachine*>(vm->impl.get()) : nullptr;
	}
}
