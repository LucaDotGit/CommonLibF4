#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_Internal_VDescTable.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) NativeFunctionStub
		: public IFunction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__NativeFunctionStub };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__NativeFunctionStub };

		~NativeFunctionStub() override; // 00

		// override (IFunction)
		const BSFixedString& GetName() const override;																											   // 01 - { return name; }
		const BSFixedString& GetObjectTypeName() const override;																								   // 02 - { return scriptName; }
		const BSFixedString& GetStateName() const override;																										   // 03 - { return stateName; }
		TypeInfo GetReturnType() const override;																												   // 04 - { return returnType; }
		std::uint32_t GetParamCount() const override;																											   // 05 - { return descTable.GetParamCount(); }
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override;													   // 06
		std::uint32_t GetStackFrameSize() const override;																										   // 07 - { return descTable.GetTotalEntryCount(); }
		bool GetIsNative() const override;																														   // 08 - { return true; }
		bool GetIsStatic() const override;																														   // 09 - { return isStatic; }
		bool GetIsEmpty() const override;																														   // 0A - { return instructions.numInstructionBits == 0; }
		FunctionType GetFunctionType() const override;																											   // 0B - { return FunctionType::kNormal; }
		UserFlags GetUserFlags() const override;																												   // 0C - { return userFlags; }
		const BSFixedString& GetDocString() const override;																										   // 0D - { return docString; }
		void InsertLocals(StackFrame& a_frame) const override;																									   // 0E
		CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const override; // 0F
		const BSFixedString& GetSourceFilename() const override;																								   // 10
		bool TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const override;															   // 11
		bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_out) const override;																   // 12
		bool CanBeCalledFromTasklets() const override;																											   // 13 - { return taskletCallable; }
		void SetCallableFromTasklets(bool a_taskletCallable) override;																							   // 14 - { taskletCallable = a_taskletCallable; }

		// members
		BSFixedString name;								  // 10
		BSFixedString scriptName;						  // 18
		BSFixedString stateName;						  // 20
		TypeInfo returnType;							  // 28
		VDescTable descTable;							  // 30
		bool isStatic;									  // 40
		bool taskletCallable;							  // 41
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 44
		BSFixedString docString;						  // 48
	};
	static_assert(sizeof(NativeFunctionStub) == 0x50);
}
