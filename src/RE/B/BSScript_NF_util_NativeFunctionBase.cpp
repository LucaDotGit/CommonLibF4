#include "RE/B/BSScript_NF_util_NativeFunctionBase.hpp"

#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_UserFlags.hpp"

namespace RE::BSScript::NF_util
{
	NativeFunctionBase::NativeFunctionBase(
		BSFixedString a_scriptName,
		BSFixedString a_funcName,
		std::uint16_t a_paramCount,
		bool a_isStatic,
		bool a_isLatent) :
		name(std::move(a_funcName)),
		scriptName(std::move(a_scriptName)),
		stateName(ObjectTypeInfo::GetEmptyStateName()),
		descTable(a_paramCount, 0),
		isStatic(a_isStatic),
		taskletCallable(false),
		isLatent(a_isLatent),
		userFlags(UserFlags::None)
	{
	}

	NativeFunctionBase::~NativeFunctionBase() = default;

	auto NativeFunctionBase::GetName() const -> const BSFixedString&
	{
		return name;
	}

	auto NativeFunctionBase::GetObjectTypeName() const -> const BSFixedString&
	{
		return scriptName;
	}

	auto NativeFunctionBase::GetStateName() const -> const BSFixedString&
	{
		return stateName;
	}

	auto NativeFunctionBase::GetReturnType() const -> TypeInfo
	{
		return returnType;
	}

	auto NativeFunctionBase::GetParamCount() const -> std::uint32_t
	{
		return descTable.GetParamCount();
	}

	void NativeFunctionBase::GetParam(std::uint32_t a_param, BSFixedString& a_paramName, TypeInfo& a_paramType) const
	{
		auto paramEntry = descTable.GetNthParamPair(static_cast<Internal::VDescTable::size_type>(a_param));
		if (!paramEntry) [[unlikely]] {
			REX::Assert(false);
			a_paramName = ""sv;
			a_paramType = nullptr;
			return;
		}

		a_paramName = paramEntry->first;
		a_paramType = paramEntry->second;
	}

	auto NativeFunctionBase::GetStackFrameSize() const -> std::uint32_t
	{
		return descTable.GetTotalEntryCount();
	}

	auto NativeFunctionBase::GetIsNative() const -> bool
	{
		return true;
	}

	auto NativeFunctionBase::GetIsStatic() const -> bool
	{
		return isStatic;
	}

	auto NativeFunctionBase::GetIsEmpty() const -> bool
	{
		return false;
	}

	auto NativeFunctionBase::GetFunctionType() const -> IFunction::FunctionType
	{
		return FunctionType::Normal;
	}

	auto NativeFunctionBase::GetUserFlags() const -> UserFlags
	{
		return userFlags.get();
	}

	auto NativeFunctionBase::GetDocString() const -> const BSFixedString&
	{
		return docString;
	}

	void NativeFunctionBase::InsertLocals([[maybe_unused]] StackFrame& a_stackFrame) const
	{
		return;
	}

	auto NativeFunctionBase::Call(
		const BSTSmartPointer<Stack>& a_stack,
		ErrorLogger& a_errorLogger,
		Internal::VirtualMachine& a_vm,
		bool a_inScriptTasklet) const -> NativeFunctionBase::CallResult
	{
		using FuncType = decltype(&NativeFunctionBase::Call);
		static const auto FUNC = REL::Relocation<FuncType>(ID::BSScript::NF_util::NativeFunctionBase::Call);
		return std::invoke(FUNC, this, a_stack, a_errorLogger, a_vm, a_inScriptTasklet);
	}

	auto NativeFunctionBase::GetSourceFilename() const -> const BSFixedString&
	{
		static const auto NATIVE_STRING = BSFixedString("<native>"sv);
		return NATIVE_STRING;
	}

	auto NativeFunctionBase::TranslateIPToLineNumber([[maybe_unused]] std::uint32_t a_ip, std::uint32_t& a_lineNumber)
		const -> bool
	{
		a_lineNumber = 0;
		return false;
	}

	auto NativeFunctionBase::GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const -> bool
	{
		auto entryName = descTable.GetNthEntryName(static_cast<Internal::VDescTable::size_type>(a_index));
		if (!entryName.has_value()) [[unlikely]] {
			REX::Assert(false);
			a_outName = ""sv;
			return false;
		}

		a_outName = std::move(entryName).value();
		return true;
	}

	auto NativeFunctionBase::CanBeCalledFromTasklets() const -> bool
	{
		return taskletCallable;
	}

	void NativeFunctionBase::SetCallableFromTasklets(bool a_taskletCallable)
	{
		taskletCallable = a_taskletCallable;
	}

	auto NativeFunctionBase::GetIsLatent() const -> bool
	{
		return isLatent;
	}
}
