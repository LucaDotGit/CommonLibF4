#include "RE/B/BSScript_Internal_VirtualMachine.hpp"

#include "RE/B/BSSpinLock.hpp"

namespace RE::BSScript::Internal
{
	auto VirtualMachine::IsStackRunning(StackID a_stackId) const noexcept -> bool
	{
		if (a_stackId == EMPTY_STACK_ID) {
			return false;
		}

		const auto stackLock = BSAutoSpinLock(runningStacksLock);
		return allRunningStacks.contains(a_stackId);
	}

	auto VirtualMachine::AttemptFunctionCall(
		Stack& a_stack,
		const BSTSmartPointer<IFuncCallQuery>& a_funcCallQuery,
		bool a_inScriptTasklet) -> bool
	{
		using FuncType = decltype(&VirtualMachine::AttemptFunctionCall);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::Internal::VirtualMachine::AttemptFunctionCall);
		return std::invoke(FUNC, this, a_stack, a_funcCallQuery, a_inScriptTasklet);
	}
}
