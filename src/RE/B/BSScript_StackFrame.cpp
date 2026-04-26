#include "RE/B/BSScript_StackFrame.hpp"

#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Stack.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"

namespace RE::BSScript
{
	std::uint32_t StackFrame::GetPageForFrame() const
	{
		if (!parentStack) [[unlikely]] {
			REX::Assert(false);
			return std::numeric_limits<std::uint32_t>::max();
		}

		return parentStack->GetPageForFrame(this);
	}

	BSTSmartPointer<Object> StackFrame::GetSelfObject() const
	{
		if (!self.IsObject()) {
			return nullptr;
		}

		return self.GetObject();
	}

	ObjectHandle StackFrame::GetSelfObjectHandle() const
	{
		if (!self.IsObject()) {
			return GameScript::HandlePolicy::EMPTY_HANDLE;
		}

		const auto selfObject = self.GetObject();
		if (!selfObject) {
			return GameScript::HandlePolicy::EMPTY_HANDLE;
		}

		return selfObject->GetHandle();
	}

	Variable* StackFrame::GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const
	{
		if (!parentStack) [[unlikely]] {
			REX::Assert(false);
			return nullptr;
		}

		return std::addressof(parentStack->GetStackFrameVariable(this, a_index, a_pageHint));
	}
}
