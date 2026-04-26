#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class IFuncCallQuery;
}

namespace RE::BSScript
{
	class Variable;

	class __declspec(novtable) IProfilePolicy
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IProfilePolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IProfilePolicy };

		virtual ~IProfilePolicy() = default; // 00

		// add
		virtual void StackFramePushQueued(StackID a_stackID, std::uint32_t a_frameNumber, const BSTSmartPointer<Internal::IFuncCallQuery>& a_funcCallQuery) = 0;																// 01
		virtual void StackFramePushed(StackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;	// 02
		virtual void StackFramePopQueued(StackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0; // 03
		virtual void StackFramePopped(StackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;	// 04
	};
	static_assert(sizeof(IProfilePolicy) == 0x08);
}
