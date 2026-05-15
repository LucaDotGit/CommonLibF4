#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_Internal_VDescTable.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	class ErrorLogger;
	class Stack;
	class StackFrame;
	class Variable;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;
}

namespace RE::BSScript::NF_util
{
	class __declspec(novtable) NativeFunctionBase
		: public IFunction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__NF_util__NativeFunctionBase };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__NF_util__NativeFunctionBase };

		NativeFunctionBase(
			std::string_view a_scriptName,
			std::string_view a_funcName,
			std::uint16_t a_paramCount,
			bool a_isStatic,
			bool a_isLatent);

		~NativeFunctionBase() override; // 00

		// override (IFunction)
		const BSFixedString& GetName() const override;																											   // 01
		const BSFixedString& GetObjectTypeName() const override;																								   // 02
		const BSFixedString& GetStateName() const override;																										   // 03
		TypeInfo GetReturnType() const override;																												   // 04
		std::uint32_t GetParamCount() const override;																											   // 05
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override;													   // 06
		std::uint32_t GetStackFrameSize() const override;																										   // 07
		bool GetIsNative() const override;																														   // 08
		bool GetIsStatic() const override;																														   // 09
		bool GetIsEmpty() const override;																														   // 0A
		FunctionType GetFunctionType() const override;																											   // 0B
		UserFlags GetUserFlags() const override;																												   // 0C
		const BSFixedString& GetDocString() const override;																										   // 0D
		void InsertLocals([[maybe_unused]] StackFrame& a_stackFrame) const override;																			   // 0E
		CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const override; // 0F
		const BSFixedString& GetSourceFilename() const override;																								   // 10
		bool TranslateIPToLineNumber([[maybe_unused]] std::uint32_t a_ip, std::uint32_t& a_lineNumber) const override;											   // 11
		bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const override;															   // 12
		bool CanBeCalledFromTasklets() const override;																											   // 13
		void SetCallableFromTasklets(bool a_taskletCallable) override;																							   // 14

		// add
		virtual bool HasStub() const = 0;																																		// 15
		virtual bool MarshallAndDispatch(Variable& a_self, Internal::VirtualMachine& a_vm, StackID a_stackID, Variable& a_outResult, const StackFrame& a_stackFrame) const = 0; // 16

		bool GetIsLatent() const;

		// members
		BSFixedString name;								  // 10
		BSFixedString scriptName;						  // 18
		BSFixedString stateName;						  // 20
		TypeInfo returnType;							  // 28
		Internal::VDescTable descTable;					  // 30
		bool isStatic;									  // 40
		bool taskletCallable;							  // 41
		bool isLatent;									  // 42
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 44
		BSFixedString docString;						  // 48
	};
	static_assert(sizeof(NativeFunctionBase) == 0x50);
}
