#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"

namespace RE::BSScript::Internal
{
	class __declspec(novtable) AutoPropGetFunction : public IFunction // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__AutoPropGetFunction;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__AutoPropGetFunction;

		~AutoPropGetFunction() override = default; // 0x00

		// override (IFunction)
		auto GetName() const -> const BSFixedString& override;			 // 0x01 - { return propertyName; }
		auto GetObjectTypeName() const -> const BSFixedString& override; // 0x02 - { return scriptName; }
		auto GetStateName() const -> const BSFixedString& override;		 // 0x03
		auto GetReturnType() const -> TypeInfo override;				 // 0x04 - { return returnType; }
		auto GetParamCount() const -> std::uint32_t override;			 // 0x05 - { return 0; }
		void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const override; // 0x06
		auto GetStackFrameSize() const -> std::uint32_t override;	// 0x07 - { return 0; }
		auto GetIsNative() const -> bool override;					// 0x08 - { return false; }
		auto GetIsStatic() const -> bool override;					// 0x09 - { return false; }
		auto GetIsEmpty() const -> bool override;					// 0x0A - { return false; }
		auto GetFunctionType() const -> FunctionType override;		// 0x0B - { return FunctionType::PropertyGetter; }
		auto GetUserFlags() const -> UserFlags override;			// 0x0C - { return UserFlags::None; }
		auto GetDocString() const -> const BSFixedString& override; // 0x0D
		void InsertLocals(StackFrame& a_frame) const override;		// 0x0E
		auto Call(
			const BSTSmartPointer<Stack>& a_stack,
			ErrorLogger& a_errorLogger,
			Internal::VirtualMachine& a_vm,
			bool a_inScriptTasklet) const -> CallResult override;											  // 0x0F
		auto GetSourceFilename() const -> const BSFixedString& override;									  // 0x10
		auto TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const -> bool override; // 0x11
		auto GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const -> bool override; // 0x12
		auto CanBeCalledFromTasklets() const -> bool override;		   // 0x13 - { return true; }
		void SetCallableFromTasklets(bool a_taskletCallable) override; // 0x14 - { return; }

		// members
		BSFixedString scriptName;	// 0x10
		BSFixedString propertyName; // 0x18
		TypeInfo returnType;		// 0x20
		std::uint32_t varIndex;		// 0x28
	};

	static_assert(sizeof(AutoPropGetFunction) == 0x30);
}
