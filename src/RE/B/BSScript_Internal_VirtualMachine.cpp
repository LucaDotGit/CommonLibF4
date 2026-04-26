#include "RE/B/BSScript_Internal_VirtualMachine.hpp"

namespace RE::BSScript::Internal
{
	bool VirtualMachine::IsStackRunning(StackID a_stackId) const
	{
		if (a_stackId == EMPTY_STACK_ID) {
			return false;
		}

		const auto stackLock = BSAutoLock(runningStacksLock);
		return allRunningStacks.contains(a_stackId);
	}
}
