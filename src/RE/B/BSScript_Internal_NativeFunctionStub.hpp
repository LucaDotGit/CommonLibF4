#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_Internal_VDescTable.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) NativeFunctionStub : public IFunction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__NativeFunctionStub;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__NativeFunctionStub;

		~NativeFunctionStub() override; // 0x00

		// override (IFunction)
		auto GetName() const -> const BSFixedString& override;			 // 0x01 - { return name; }
		auto GetObjectTypeName() const -> const BSFixedString& override; // 0x02 - { return scriptName; }
		auto GetStateName() const -> const BSFixedString& override;		 // 0x03 - { return stateName; }
		auto GetReturnType() const -> TypeInfo override;				 // 0x04 - { return returnType; }
		auto GetParamCount() const -> std::uint32_t override;			 // 0x05 - { return descTable.GetParamCount(); }
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override; // 0x06
		auto GetStackFrameSize() const -> std::uint32_t override; // 0x07 - { return descTable.GetTotalEntryCount(); }
		auto GetIsNative() const -> bool override;				  // 0x08 - { return true; }
		auto GetIsStatic() const -> bool override;				  // 0x09 - { return isStatic; }
		auto GetIsEmpty() const -> bool override; // 0x0A - { return instructions.numInstructionBits == 0; }
		auto GetFunctionType() const -> FunctionType override;		// 0x0B - { return FunctionType::Normal; }
		auto GetUserFlags() const -> UserFlags override;			// 0x0C - { return userFlags; }
		auto GetDocString() const -> const BSFixedString& override; // 0x0D - { return docString; }
		void InsertLocals(StackFrame& a_frame) const override;		// 0x0E
		auto Call(
			const BSTSmartPointer<Stack>& a_stack,
			ErrorLogger& a_errorLogger,
			Internal::VirtualMachine& a_vm,
			bool a_inScriptTasklet) const -> CallResult override;											  // 0x0F
		auto GetSourceFilename() const -> const BSFixedString& override;									  // 0x10
		auto TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const -> bool override; // 0x11
		auto GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const -> bool override; // 0x12
		auto CanBeCalledFromTasklets() const -> bool override; // 0x13 - { return taskletCallable; }
		void SetCallableFromTasklets(
			bool a_taskletCallable) override; // 0x14 - { taskletCallable = a_taskletCallable; }

		// members
		BSFixedString name;								  // 0x10
		BSFixedString scriptName;						  // 0x18
		BSFixedString stateName;						  // 0x20
		TypeInfo returnType;							  // 0x28
		VDescTable descTable;							  // 0x30
		bool isStatic;									  // 0x40
		bool taskletCallable;							  // 0x41
		REX::EnumSet<UserFlags, std::uint32_t> userFlags; // 0x44
		BSFixedString docString;						  // 0x48
	};

	static_assert(sizeof(NativeFunctionStub) == 0x50);
}
