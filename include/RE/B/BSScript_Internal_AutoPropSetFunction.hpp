#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) AutoPropSetFunction
		: public IFunction // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__AutoPropSetFunction };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__AutoPropSetFunction };

		~AutoPropSetFunction() override = default; // 00

		// override (IFunction)
		const BSFixedString& GetName() const override;																											   // 01 - { return propertyName; }
		const BSFixedString& GetObjectTypeName() const override;																								   // 02 - { return scriptName; }
		const BSFixedString& GetStateName() const override;																										   // 03
		TypeInfo GetReturnType() const override;																												   // 04 - { return returnType; }
		std::uint32_t GetParamCount() const override;																											   // 05 - { return 1; }
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override;													   // 06
		std::uint32_t GetStackFrameSize() const override;																										   // 07 - { return 1; }
		bool GetIsNative() const override;																														   // 08 - { return false; }
		bool GetIsStatic() const override;																														   // 09 - { return false; }
		bool GetIsEmpty() const override;																														   // 0A - { return false; }
		FunctionType GetFunctionType() const override;																											   // 0B - { return FunctionType::kPropertySetter; }
		UserFlags GetUserFlags() const override;																												   // 0C - { return UserFlags::kNone; }
		const BSFixedString& GetDocString() const override;																										   // 0D
		void InsertLocals(StackFrame& a_frame) const override;																									   // 0E
		CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const override; // 0F
		const BSFixedString& GetSourceFilename() const override;																								   // 10
		bool TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const override;															   // 11
		bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const override;															   // 12
		bool CanBeCalledFromTasklets() const override;																											   // 13 - { return true; }
		void SetCallableFromTasklets(bool a_taskletCallable) override;																							   // 14 - { return; }

		// members
		BSFixedString scriptName;	// 10
		BSFixedString propertyName; // 18
		TypeInfo returnType;		// 20
		std::uint32_t varIndex;		// 28
	};
	static_assert(sizeof(AutoPropSetFunction) == 0x30);
}
