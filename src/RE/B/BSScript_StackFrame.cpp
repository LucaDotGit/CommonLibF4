#include "RE/B/BSScript_StackFrame.hpp"

#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Stack.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"

namespace RE::BSScript
{
	auto StackFrame::GetPageForFrame() const -> std::uint32_t
	{
		if (!parentStack) {
			return std::numeric_limits<std::uint32_t>::max();
		}

		return parentStack->GetPageForFrame(this);
	}

	auto StackFrame::GetSelfObject() const -> BSTSmartPointer<Object>
	{
		if (!self.IsObject()) {
			return nullptr;
		}

		return self.GetObject();
	}

	auto StackFrame::GetSelfObjectHandle() const -> ObjectHandle
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

	auto StackFrame::GetStackFrameVariable(std::uint32_t a_index, std::uint32_t a_pageHint) const -> const Variable*
	{
		if (!parentStack) {
			return nullptr;
		}

		return std::addressof(parentStack->GetStackFrameVariable(this, a_index, a_pageHint));
	}
}
