#include "RE/B/BSScript_NF_util_NativeFunctionBase.hpp"

namespace RE::BSScript::NF_util
{
	NativeFunctionBase::NativeFunctionBase(
		std::string_view a_scriptName,
		std::string_view a_funcName,
		std::uint16_t a_paramCount,
		bool a_isStatic,
		bool a_isLatent)
		: name(a_funcName),
		  scriptName(a_scriptName),
		  stateName(""sv),
		  descTable(a_paramCount, 0),
		  isStatic(a_isStatic),
		  taskletCallable(false),
		  isLatent(a_isLatent),
		  userFlags(0),
		  docString(""sv)
	{
	}

	NativeFunctionBase::~NativeFunctionBase() = default;

	const BSFixedString& NativeFunctionBase::GetName() const
	{
		return name;
	}

	const BSFixedString& NativeFunctionBase::GetObjectTypeName() const
	{
		return scriptName;
	}

	const BSFixedString& NativeFunctionBase::GetStateName() const
	{
		return stateName;
	}

	TypeInfo NativeFunctionBase::GetReturnType() const
	{
		return returnType;
	}

	std::uint32_t NativeFunctionBase::GetParamCount() const
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

	std::uint32_t NativeFunctionBase::GetStackFrameSize() const
	{
		return descTable.GetTotalEntryCount();
	}

	bool NativeFunctionBase::GetIsNative() const
	{
		return true;
	}

	bool NativeFunctionBase::GetIsStatic() const
	{
		return isStatic;
	}

	bool NativeFunctionBase::GetIsEmpty() const
	{
		return false;
	}

	IFunction::FunctionType NativeFunctionBase::GetFunctionType() const
	{
		return FunctionType::kNormal;
	}

	UserFlags NativeFunctionBase::GetUserFlags() const
	{
		return userFlags.get();
	}

	const BSFixedString& NativeFunctionBase::GetDocString() const
	{
		return docString;
	}

	void NativeFunctionBase::InsertLocals([[maybe_unused]] StackFrame& a_stackFrame) const
	{
		return;
	}

	NativeFunctionBase::CallResult NativeFunctionBase::Call(const BSTSmartPointer<Stack>& a_stack, ErrorLogger& a_errorLogger, Internal::VirtualMachine& a_vm, bool a_inScriptTasklet) const
	{
		using FuncType = decltype(&NativeFunctionBase::Call);
		static const auto FUNC = REL::Relocation<FuncType>{ ID::BSScript::NF_util::NativeFunctionBase::Call };
		return std::invoke(FUNC, this, a_stack, a_errorLogger, a_vm, a_inScriptTasklet);
	}

	const BSFixedString& NativeFunctionBase::GetSourceFilename() const
	{
		static const auto NATIVE_STRING = BSFixedString("<native>"sv);
		return NATIVE_STRING;
	}

	bool NativeFunctionBase::TranslateIPToLineNumber([[maybe_unused]] std::uint32_t a_ip, std::uint32_t& a_lineNumber) const
	{
		a_lineNumber = 0;
		return false;
	}

	bool NativeFunctionBase::GetVarNameForStackIndex(std::uint32_t a_index, BSFixedString& a_outName) const
	{
		auto entryName = descTable.GetNthEntryName(static_cast<Internal::VDescTable::size_type>(a_index));
		if (!entryName) [[unlikely]] {
			REX::Assert(false);
			a_outName = ""sv;
			return false;
		}

		a_outName = *std::move(entryName);
		return true;
	}

	bool NativeFunctionBase::CanBeCalledFromTasklets() const
	{
		return taskletCallable;
	}

	void NativeFunctionBase::SetCallableFromTasklets(bool a_taskletCallable)
	{
		taskletCallable = a_taskletCallable;
	}

	bool NativeFunctionBase::GetIsLatent() const
	{
		return isLatent;
	}
}
