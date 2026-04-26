#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_Variant.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSContainer
{
	enum class ForEachResult : std::int32_t;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;
}

namespace RE::BSScript
{
	enum class UserFlags : std::uint32_t;

	class ErrorLogger;
	class Stack;
	class StackFrame;
	class TypeInfo;
	class Variable;

	class __declspec(novtable) IFunction
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IFunction };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IFunction };

		enum class CallResult : std::int32_t
		{
			kCompleted = 0,
			kSetupForVM = 1,
			kInProgress = 2,
			kFailedRetry = 3,
			kFailedAbort = 4
		};

		enum class FunctionType : std::int32_t
		{
			kNormal = 0,
			kPropertyGetter = 1,
			kPropertySetter = 2
		};

		virtual ~IFunction() = default; // 00

		// add
		virtual const BSFixedString& GetName() const = 0;																											  // 01
		virtual const BSFixedString& GetObjectTypeName() const = 0;																									  // 02
		virtual const BSFixedString& GetStateName() const = 0;																										  // 03
		virtual TypeInfo GetReturnType() const = 0;																													  // 04
		virtual std::uint32_t GetParamCount() const = 0;																											  // 05
		virtual void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const = 0;													  // 06
		virtual std::uint32_t GetStackFrameSize() const = 0;																										  // 07
		virtual bool GetIsNative() const = 0;																														  // 08
		virtual bool GetIsStatic() const = 0;																														  // 09
		virtual bool GetIsEmpty() const = 0;																														  // 0A
		virtual FunctionType GetFunctionType() const = 0;																											  // 0B
		virtual UserFlags GetUserFlags() const = 0;																													  // 0C
		virtual const BSFixedString& GetDocString() const = 0;																										  // 0D
		virtual void InsertLocals(StackFrame& a_frame) const = 0;																									  // 0E
		virtual CallResult Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const = 0; // 0F
		virtual const BSFixedString& GetSourceFilename() const = 0;																									  // 10
		virtual bool TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const = 0;															  // 11
		virtual bool GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_variableName) const = 0;														  // 12
		virtual bool CanBeCalledFromTasklets() const = 0;																											  // 13
		virtual void SetCallableFromTasklets(bool a_taskletCallable) = 0;																							  // 14

		[[nodiscard]] bool HasNoParams() const;

		[[nodiscard]] bool HasParamsOfTypes(std::span<const TypeInfo> a_args) const;
		[[nodiscard]] bool HasParamsOfTypes(std::span<const Variable> a_args) const;

		[[nodiscard]] bool HasParamsOfVariadicTypes(std::span<const Variable> a_args) const;
		[[nodiscard]] bool HasParamsOfVariadicTypes(std::span<const SharedVariant> a_args) const;
		[[nodiscard]] bool HasParamsOfVariadicTypes(std::span<const UniqueVariant> a_args) const;

		[[nodiscard]] auto GetParamNames() const -> std::vector<BSFixedString>;
		[[nodiscard]] auto GetParamTypes() const -> std::vector<TypeInfo>;
		[[nodiscard]] auto GetParams() const -> std::vector<std::pair<BSFixedString, TypeInfo>>;

		BSContainer::ForEachResult ForEachParam(
			const REX::NotNull<std::function<BSContainer::ForEachResult(std::uint32_t, const BSFixedString&, const TypeInfo&)>>& a_predicate) const;
	};
	static_assert(sizeof(IFunction) == 0x10);
}
