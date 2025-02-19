#pragma once

#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class Variable;

	namespace Internal
	{
		class IFuncCallQuery;
	}

	class __declspec(novtable) IProfilePolicy
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IProfilePolicy };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IProfilePolicy };

		virtual ~IProfilePolicy() = default; // 00

		// add
		virtual void StackFramePushQueued(VMStackID a_stackID, std::uint32_t a_frameNumber, const BSTSmartPointer<Internal::IFuncCallQuery>& a_funcCallQuery) = 0;																  // 01
		virtual void StackFramePushed(VMStackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;	  // 02
		virtual void StackFramePopQueued(VMStackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0; // 03
		virtual void StackFramePopped(VMStackID a_stackID, std::uint32_t a_frameNumber, const Variable& a_self, const BSFixedString& a_scriptName, const BSFixedString& a_stateName, const BSFixedString& a_functionName) = 0;	  // 04
	};
	static_assert(sizeof(IProfilePolicy) == 0x8);
}
