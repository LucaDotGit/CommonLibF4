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
	class __declspec(novtable) NativeFunctionBase : public IFunction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__NF_util__NativeFunctionBase;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__NF_util__NativeFunctionBase;

		NativeFunctionBase(
			BSFixedString a_scriptName,
			BSFixedString a_funcName,
			std::uint16_t a_paramCount,
			bool a_isStatic,
			bool a_isLatent);

		~NativeFunctionBase() override; // 0x00

		// override (IFunction)
		auto GetName() const -> const BSFixedString& override;													// 0x01
		auto GetObjectTypeName() const -> const BSFixedString& override;										// 0x02
		auto GetStateName() const -> const BSFixedString& override;												// 0x03
		auto GetReturnType() const -> TypeInfo override;														// 0x04
		auto GetParamCount() const -> std::uint32_t override;													// 0x05
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override; // 0x06
		auto GetStackFrameSize() const -> std::uint32_t override;												// 0x07
		auto GetIsNative() const -> bool override;																// 0x08
		auto GetIsStatic() const -> bool override;																// 0x09
		auto GetIsEmpty() const -> bool override;																// 0x0A
		auto GetFunctionType() const -> FunctionType override;													// 0x0B
		auto GetUserFlags() const -> UserFlags override;														// 0x0C
		auto GetDocString() const -> const BSFixedString& override;												// 0x0D
		void InsertLocals(StackFrame& a_stackFrame) const override;												// 0x0E
		auto Call(
			const BSTSmartPointer<Stack>& a_stack,
			ErrorLogger& a_errorLogger,
			Internal::VirtualMachine& a_vm,
			bool a_inScriptTasklet) const -> CallResult override;											  // 0x0F
		auto GetSourceFilename() const -> const BSFixedString& override;									  // 0x10
		auto TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const -> bool override; // 0x11
		auto GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const -> bool override; // 0x12
		auto CanBeCalledFromTasklets() const -> bool override;												  // 0x13
		void SetCallableFromTasklets(bool a_taskletCallable) override;										  // 0x14

		// add
		virtual auto HasStub() const -> bool = 0; // 0x15
		virtual auto MarshallAndDispatch(
			Variable& a_self,
			Internal::VirtualMachine& a_vm,
			StackID a_stackID,
			Variable& a_outResult,
			const StackFrame& a_stackFrame) const -> bool = 0; // 0x16

		auto GetIsLatent() const -> bool;

		// members
		BSFixedString name;								  // 0x10
		BSFixedString scriptName;						  // 0x18
		BSFixedString stateName;						  // 0x20
		TypeInfo returnType;							  // 0x28
		Internal::VDescTable descTable;					  // 0x30
		bool isStatic;									  // 0x40
		bool taskletCallable;							  // 0x41
		bool isLatent;									  // 0x42
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 0x44
		BSFixedString docString;						  // 0x48
	};

	static_assert(sizeof(NativeFunctionBase) == 0x50);
}
