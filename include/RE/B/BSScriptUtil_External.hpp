#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScriptUtil_Core.hpp"
#include "RE/B/BSScriptUtil_LatentResult.hpp"
#include "RE/B/BSScriptUtil_NativeFunction.hpp"
#include "RE/B/BSScript_IStackCallbackFunctor.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	template <class... Args>
	bool IVirtualMachine::InvokeMemberFunction(
		const BSTSmartPointer<Object>& a_self,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args)
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = BSScript::CreateThreadScrapFunction(std::forward<Args>(a_args)...);
		return DispatchMethodCall(a_self, a_funcName, argsFactory, a_callbackFunctor);
	}

	template <class... Args>
	bool IVirtualMachine::InvokeStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args)
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = BSScript::CreateThreadScrapFunction(std::forward<Args>(a_args)...);
		return DispatchStaticCall(a_scriptName, a_funcName, argsFactory, a_callbackFunctor);
	}

	bool IVirtualMachine::InvokeAppliedMemberFunction(
		const BSTSmartPointer<Object>& a_self,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		std::span<const Variable> a_args)
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(a_args);
		return DispatchMethodCall(a_self, a_funcName, argsFactory, a_callbackFunctor);
	}

	bool IVirtualMachine::InvokeAppliedMemberFunction(
		const BSTSmartPointer<Object>& a_self,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		BSScrapArray<Variable>&& a_args)
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(std::move(a_args));
		return DispatchMethodCall(a_self, a_funcName, argsFactory, a_callbackFunctor);
	}

	bool IVirtualMachine::InvokeAppliedStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		std::span<const Variable> a_args)
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(a_args);
		return DispatchStaticCall(a_scriptName, a_funcName, argsFactory, a_callbackFunctor);
	}

	bool IVirtualMachine::InvokeAppliedStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		BSScrapArray<Variable>&& a_args)
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(std::move(a_args));
		return DispatchStaticCall(a_scriptName, a_funcName, argsFactory, a_callbackFunctor);
	}

	inline void IVirtualMachine::ReturnLatentFunction(
		StackID a_stackID)
	{
		ReturnFromLatent(a_stackID, BSScript::NONE_VARIABLE);
	}

	template <class T>
	void IVirtualMachine::ReturnLatentFunction(
		StackID a_stackID,
		T&& a_result)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto result = Variable();
		Impl::PackVariable(result, std::forward<T>(a_result));
		ReturnFromLatent(a_stackID, result);
	}

	inline LatentResult<void> IVirtualMachine::ReturnLatentResult(
		StackID a_stackID)
	{
		ReturnLatentFunction(a_stackID);
		return { LatentStatus::kStarted };
	}

	template <class T>
	LatentResult<std::remove_reference_t<T>> IVirtualMachine::ReturnLatentResult(
		StackID a_stackID,
		T&& a_result)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		ReturnLatentFunction(a_stackID, std::forward<T>(a_result));
		return { LatentStatus::kStarted };
	}

	template <class T>
	bool IVirtualMachine::BindNativeFunction(
		REX::zstring_view a_scriptName,
		REX::zstring_view a_funcName,
		const T& a_func,
		bool a_taskletCallable)
		requires(requires { NativeFunction(a_scriptName, a_funcName, a_func); })
	{
		REX::Assert(REX::IsNullTerminated(a_scriptName));
		REX::Assert(REX::IsNullTerminated(a_funcName));

		const auto isBound =
			BindNativeMethod(
				new NativeFunction(
					a_scriptName,
					a_funcName,
					a_func));

		if (!isBound) [[unlikely]] {
			REX::LogError(R"(Failed to register function "{}" on script "{}")"sv,
				a_funcName, a_scriptName);
			REX::Assert(false);
			return false;
		}

		if (a_taskletCallable) {
			SetCallableFromTasklets(a_scriptName.data(), a_funcName.data(), true);
		}

		return true;
	}

	template <class T>
	bool IVirtualMachine::BindNativeLatentFunction(
		REX::zstring_view a_scriptName,
		REX::zstring_view a_funcName,
		const T& a_func,
		bool a_taskletCallable)
		requires(requires { NativeLatentFunction(a_scriptName, a_funcName, a_func); })
	{
		REX::Assert(REX::IsNullTerminated(a_scriptName));
		REX::Assert(REX::IsNullTerminated(a_funcName));

		const auto isBound =
			BindNativeMethod(
				new NativeLatentFunction(
					a_scriptName,
					a_funcName,
					a_func));

		if (!isBound) [[unlikely]] {
			REX::LogError(R"(Failed to register function "{}" on script "{}")"sv,
				a_funcName, a_scriptName);
			REX::Assert(false);
			return false;
		}

		if (a_taskletCallable) {
			SetCallableFromTasklets(a_scriptName.data(), a_funcName.data(), true);
		}

		return true;
	}

	template <class... Args>
	void IVirtualMachine::PostMessage(
		REX::FormatString<Args...> a_format,
		StackID a_stackID,
		ErrorLogger::Severity a_severity,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		PostMessage(REX::zstring_view{ formatData.buffer.data(), formatData.size }, a_stackID, a_severity);
	}

	template <class... Args>
	void IVirtualMachine::PostInfo(
		REX::FormatString<Args...> a_format,
		StackID a_stackID,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		PostInfo(REX::zstring_view{ formatData.buffer.data(), formatData.size }, a_stackID);
	}

	template <class... Args>
	void IVirtualMachine::PostWarning(
		REX::FormatString<Args...> a_format,
		StackID a_stackID,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		PostWarning(REX::zstring_view{ formatData.buffer.data(), formatData.size }, a_stackID);
	}

	template <class... Args>
	void IVirtualMachine::PostError(
		REX::FormatString<Args...> a_format,
		StackID a_stackID,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		PostError(REX::zstring_view{ formatData.buffer.data(), formatData.size }, a_stackID);
	}

	template <class... Args>
	void IVirtualMachine::PostFatal(
		REX::FormatString<Args...> a_format,
		StackID a_stackID,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		const auto formatData = REX::FixedFormat(a_format, std::forward<Args>(a_args)...);
		PostFatal(REX::zstring_view{ formatData.buffer.data(), formatData.size }, a_stackID);
	}

	template <class T>
	auto Object::FindVariable(REX::zstring_view a_name) const
		-> std::optional<T>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return std::nullopt;
		}

		const auto objectLock = BSAutoLock(*this);
		return Impl::UnpackVariable<T>(*variable);
	}

	template <class T>
	T Object::FindVariableOrDefault(REX::zstring_view a_name) const
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return {};
		}

		const auto objectLock = BSAutoLock(*this);
		return Impl::UnpackVariable<T>(*variable);
	}

	template <class T>
	auto Object::FindProperty(REX::zstring_view a_name) const
		-> std::optional<T>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* property = GetProperty(BSFixedString(a_name));
		if (!property) {
			return std::nullopt;
		}

		const auto objectLock = BSAutoLock(*this);
		return Impl::UnpackVariable<T>(*property);
	}

	template <class T>
	T Object::FindPropertyOrDefault(REX::zstring_view a_name) const
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* property = GetProperty(BSFixedString(a_name));
		if (!property) {
			return {};
		}

		const auto objectLock = BSAutoLock(*this);
		return Impl::UnpackVariable<T>(*property);
	}

	template <class T>
	bool Object::InsertVariable(REX::zstring_view a_name, T&& a_value)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return false;
		}

		const auto objectLock = BSAutoLock(*this);
		Impl::PackVariable(*variable, std::forward<T>(a_value));
		return true;
	}

	template <class T>
	bool Object::InsertProperty(REX::zstring_view a_name, T&& a_value)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* property = GetProperty(BSFixedString(a_name));
		if (!property) {
			return false;
		}

		const auto objectLock = BSAutoLock(*this);
		Impl::PackVariable(*property, std::forward<T>(a_value));
		return true;
	}

	template <class T>
	auto Struct::Find(REX::zstring_view a_name) const
		-> std::optional<T>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return std::nullopt;
		}

		const auto structureLock = BSAutoLock(structLock);
		return Impl::UnpackVariable<T>(*variable);
	}

	template <class T>
	T Struct::FindOrDefault(REX::zstring_view a_name) const
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return {};
		}

		const auto structureLock = BSAutoLock(structLock);
		return Impl::UnpackVariable<T>(*variable);
	}

	template <class T>
	T Struct::FindOrDefault(REX::zstring_view a_name, const T& a_default) const
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return a_default;
		}

		const auto structureLock = BSAutoLock(structLock);
		return Impl::UnpackVariable<T>(*variable);
	}

	template <class T>
	bool Struct::Insert(REX::zstring_view a_name, T&& a_value)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return false;
		}

		const auto structureLock = BSAutoLock(structLock);
		Impl::PackVariable(*variable, std::forward<T>(a_value));
		return true;
	}

	template <class T>
	void Variable::Pack(T&& a_value)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		Impl::PackVariable(*this, std::forward<T>(a_value));
	}

	template <class T>
	T Variable::Unpack() const
		requires(BSScript::ValidateParameter<T>())
	{
		return Impl::UnpackVariable<T>(*this);
	}
}

#define BASIC_RE_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, a_taskletCallable)                     \
	if (!(a_vm).BindNativeFunction(a_scriptName, #a_func##sv, a_func, a_taskletCallable)) [[unlikely]] { \
		REX::Assert(false);                                                                              \
	}

#define BASIC_REGISTER_VM_LATENT_FUNCTION(a_vm, a_scriptName, a_func, a_taskletCallable)                       \
	if (!(a_vm).BindNativeLatentFunction(a_scriptName, #a_func##sv, a_func, a_taskletCallable)) [[unlikely]] { \
		REX::Assert(false);                                                                                    \
	}

#define RE_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func) \
	BASIC_RE_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, false)

#define RE_REGISTER_VM_FUNCTION_ASYNC(a_vm, a_scriptName, a_func) \
	BASIC_RE_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, true)

#define RE_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func) \
	BASIC_REGISTER_VM_LATENT_FUNCTION(a_vm, a_scriptName, a_func, false)

#define RE_REGISTER_VM_FUNCTION_LATENT_ASYNC(a_vm, a_scriptName, a_func) \
	BASIC_REGISTER_VM_LATENT_FUNCTION(a_vm, a_scriptName, a_func, true)
