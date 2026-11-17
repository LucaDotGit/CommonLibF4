#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScript_Variant.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTTuple.hpp"

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

	class __declspec(novtable) IFunction : public BSIntrusiveRefCounted // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IFunction;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IFunction;

		enum class CallResult : std::int32_t
		{
			Completed = 0,
			SetupForVM = 1,
			InProgress = 2,
			FailedRetry = 3,
			FailedAbort = 4
		};

		enum class FunctionType : std::int32_t
		{
			Normal = 0,
			PropertyGetter = 1,
			PropertySetter = 2
		};

		virtual ~IFunction() = default; // 0x00

		// add
		virtual auto GetName() const -> const BSFixedString& = 0;			// 0x01
		virtual auto GetObjectTypeName() const -> const BSFixedString& = 0; // 0x02
		virtual auto GetStateName() const -> const BSFixedString& = 0;		// 0x03
		virtual auto GetReturnType() const -> TypeInfo = 0;					// 0x04
		virtual auto GetParamCount() const -> std::uint32_t = 0;			// 0x05
		virtual void GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType)
			const = 0;												   // 0x06
		virtual auto GetStackFrameSize() const -> std::uint32_t = 0;   // 0x07
		virtual auto GetIsNative() const -> bool = 0;				   // 0x08
		virtual auto GetIsStatic() const -> bool = 0;				   // 0x09
		virtual auto GetIsEmpty() const -> bool = 0;				   // 0x0A
		virtual auto GetFunctionType() const -> FunctionType = 0;	   // 0x0B
		virtual auto GetUserFlags() const -> UserFlags = 0;			   // 0x0C
		virtual auto GetDocString() const -> const BSFixedString& = 0; // 0x0D
		virtual void InsertLocals(StackFrame& a_frame) const = 0;	   // 0x0E
		virtual auto Call(
			const BSTSmartPointer<Stack>& a_stack,
			ErrorLogger& a_errorLogger,
			Internal::VirtualMachine& a_vm,
			bool a_inScriptTasklet) const -> CallResult = 0;													 // 0x0F
		virtual auto GetSourceFilename() const -> const BSFixedString& = 0;										 // 0x10
		virtual auto TranslateIPToLineNumber(std::uint32_t a_ip, std::uint32_t& a_lineNumber) const -> bool = 0; // 0x11
		virtual auto GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const -> bool = 0; // 0x12
		virtual auto CanBeCalledFromTasklets() const -> bool = 0;												 // 0x13
		virtual void SetCallableFromTasklets(bool a_taskletCallable) = 0;										 // 0x14

		[[nodiscard]]
		auto HasNoParams() const -> bool;

		[[nodiscard]]
		auto HasParamsOfTypes(std::span<const TypeInfo> a_args) const -> bool;
		[[nodiscard]]
		auto HasParamsOfTypes(std::span<const Variable> a_args) const -> bool;

		[[nodiscard]]
		auto HasParamsOfVariadicTypes(std::span<const Variable> a_args) const -> bool;
		[[nodiscard]]
		auto HasParamsOfVariadicTypes(std::span<const SharedVariant> a_args) const -> bool;
		[[nodiscard]]
		auto HasParamsOfVariadicTypes(std::span<const UniqueVariant> a_args) const -> bool;

		[[nodiscard]]
		auto GetParamNames() const -> BSTArray<BSFixedString>;
		[[nodiscard]]
		auto GetParamTypes() const -> BSTArray<TypeInfo>;
		[[nodiscard]]
		auto GetParams() const -> BSTArray<BSTPair<BSFixedString, TypeInfo>>;

		auto ForEachParam(
			const REX::NotNull<std::move_only_function<
				BSContainer::ForEachResult(std::uint32_t, const BSFixedString&, const TypeInfo&) const>>& a_predicate)
			const -> BSContainer::ForEachResult;
	};

	static_assert(sizeof(IFunction) == 0x10);
}
