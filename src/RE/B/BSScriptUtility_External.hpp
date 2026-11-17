#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScriptUtility_Core.hpp"
#include "RE/B/BSScriptUtility_LatentResult.hpp"
#include "RE/B/BSScriptUtility_NativeFunction.hpp"
#include "RE/B/BSScript_IStackCallbackFunctor.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_LogSeverity.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_Struct.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTSmartPointer.hpp"

namespace RE::BSScript
{
	template <class... Args>
	auto IVirtualMachine::InvokeMemberFunction(
		const BSTSmartPointer<Object>& a_self,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args) -> bool
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = BSScript::CreateThreadScrapFunction(*this, std::forward<Args>(a_args)...);
		return DispatchMethodCall(a_self, a_funcName, argsFactory, a_callbackFunctor);
	}

	template <class... Args>
	auto IVirtualMachine::InvokeStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		Args&&... a_args) -> bool
		requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...))
	{
		const auto argsFactory = BSScript::CreateThreadScrapFunction(*this, std::forward<Args>(a_args)...);
		return DispatchStaticCall(a_scriptName, a_funcName, argsFactory, a_callbackFunctor);
	}

	auto IVirtualMachine::InvokeAppliedMemberFunction(
		const BSTSmartPointer<Object>& a_self,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		std::span<const Variable> a_args) -> bool
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(a_args);
		return DispatchMethodCall(a_self, a_funcName, argsFactory, a_callbackFunctor);
	}

	auto IVirtualMachine::InvokeAppliedStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
		std::span<const Variable> a_args) -> bool
	{
		const auto argsFactory = BSScript::CreateAppliedThreadScrapFunction(a_args);
		return DispatchStaticCall(a_scriptName, a_funcName, argsFactory, a_callbackFunctor);
	}

	void IVirtualMachine::ReturnLatentFunction(StackID a_stackID)
	{
		ReturnFromLatent(a_stackID, BSScript::NONE_VARIABLE);
	}

	template <class T>
	void IVirtualMachine::ReturnLatentFunction(StackID a_stackID, T&& a_result)
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto result = Variable();
		Impl::PackVariable(*this, result, std::forward<T>(a_result));
		ReturnFromLatent(a_stackID, result);
	}

	auto IVirtualMachine::ReturnLatentResult(StackID a_stackID) -> LatentResult<void>
	{
		ReturnLatentFunction(a_stackID);
		return {LatentStatus::Started};
	}

	template <class T>
	auto IVirtualMachine::ReturnLatentResult(StackID a_stackID, T&& a_result)
		-> LatentResult<std::remove_reference_t<T>>
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		ReturnLatentFunction(a_stackID, std::forward<T>(a_result));
		return {LatentStatus::Started};
	}

	template <class T>
	auto IVirtualMachine::BindNativeFunction(
		REX::ZStringView a_scriptName,
		REX::ZStringView a_funcName,
		const T& a_func,
		bool a_taskletCallable,
		bool a_terminateOnFailure) -> bool
		requires(requires { NativeFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func); })
	{
		REX::Assert(REX::IsNullTerminated(a_scriptName));
		REX::Assert(REX::IsNullTerminated(a_funcName));

		const auto isBound =
			BindNativeMethod(new NativeFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func));

		if (!isBound) [[unlikely]] {
			if (!a_terminateOnFailure) {
				return false;
			}

			REX::Fail(R"(Failed to bind script function "{}.{}".)"sv, a_scriptName, a_funcName);
		}

		if (a_taskletCallable) {
			SetCallableFromTasklets(a_scriptName.data(), a_funcName.data(), true);
		}

		return true;
	}

	template <class T>
	auto IVirtualMachine::BindNativeLatentFunction(
		REX::ZStringView a_scriptName,
		REX::ZStringView a_funcName,
		const T& a_func,
		bool a_taskletCallable,
		bool a_terminateOnFailure) -> bool
		requires(requires {
			NativeLatentFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func);
		})
	{
		REX::Assert(REX::IsNullTerminated(a_scriptName));
		REX::Assert(REX::IsNullTerminated(a_funcName));

		const auto isBound = BindNativeMethod(
			new NativeLatentFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func));

		if (!isBound) [[unlikely]] {
			if (!a_terminateOnFailure) {
				return false;
			}

			REX::Fail(R"(Failed to bind latent script function "{}.{}".)"sv, a_scriptName, a_funcName);
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
		LogSeverity a_severity,
		Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		auto formatStorage = REX::StaticString<REX::MESSAGE_BUFFER_SIZE>();
		auto formatRessource = std::pmr::monotonic_buffer_resource{formatStorage.data(), formatStorage.size()};
		auto formatBuffer = std::pmr::string(std::addressof(formatRessource));

		REX::FormatTo(std::back_inserter(formatBuffer), a_format, std::forward<Args>(a_args)...);
		PostMessage(std::string_view{formatBuffer.data(), formatBuffer.size()}, a_stackID, a_severity);
	}

	void IVirtualMachine::PostInfo(REX::ZStringView a_message, StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, LogSeverity::Info);
	}

	template <class... Args>
	void IVirtualMachine::PostInfo(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		PostMessage(a_format, a_stackID, LogSeverity::Info, std::forward<Args>(a_args)...);
	}

	void IVirtualMachine::PostWarning(REX::ZStringView a_message, StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, LogSeverity::Warning);
	}

	template <class... Args>
	void IVirtualMachine::PostWarning(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		PostMessage(a_format, a_stackID, LogSeverity::Warning, std::forward<Args>(a_args)...);
	}

	void IVirtualMachine::PostError(REX::ZStringView a_message, StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, LogSeverity::Error);
	}

	template <class... Args>
	void IVirtualMachine::PostError(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		PostMessage(a_format, a_stackID, LogSeverity::Error, std::forward<Args>(a_args)...);
	}

	void IVirtualMachine::PostFatal(REX::ZStringView a_message, StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, LogSeverity::Fatal);
	}

	template <class... Args>
	void IVirtualMachine::PostFatal(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
		requires((REX::formattable<Args, char> && ...))
	{
		PostMessage(a_format, a_stackID, LogSeverity::Fatal, std::forward<Args>(a_args)...);
	}

	template <class T>
	auto Object::FindVariable(IVirtualMachine& a_vm, REX::ZStringView a_name) const
		-> std::optional<std::remove_cv_t<T>>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return std::nullopt;
		}

		const auto objectLock = BSAutoSpinLock(*this);
		return Impl::UnpackVariable<T>(a_vm, *variable);
	}

	template <class T>
	auto Object::InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return false;
		}

		const auto objectLock = BSAutoSpinLock(*this);
		return Impl::PackVariable(a_vm, *variable, std::forward<T>(a_value));
	}

	template <class T>
	auto Object::FindProperty(IVirtualMachine& a_vm, REX::ZStringView a_name) const
		-> std::optional<std::remove_cv_t<T>>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* property = GetProperty(BSFixedString(a_name));
		if (!property) {
			return std::nullopt;
		}

		const auto objectLock = BSAutoSpinLock(*this);
		return Impl::UnpackVariable<T>(a_vm, *property);
	}

	template <class T>
	auto Object::InsertProperty(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* property = GetProperty(BSFixedString(a_name));
		if (!property) {
			return false;
		}

		const auto objectLock = BSAutoSpinLock(*this);
		return Impl::PackVariable(a_vm, *property, std::forward<T>(a_value));
	}

	template <class T>
	auto Struct::FindVariable(IVirtualMachine& a_vm, REX::ZStringView a_name) const
		-> std::optional<std::remove_cv_t<T>>
		requires(BSScript::ValidateParameter<T>())
	{
		const auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return std::nullopt;
		}

		const auto structureLock = BSAutoSpinLock(structLock);
		return Impl::UnpackVariable<T>(a_vm, *variable);
	}

	template <class T>
	auto Struct::InsertVariable(IVirtualMachine& a_vm, REX::ZStringView a_name, T&& a_value) -> bool
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		auto* variable = GetVariable(BSFixedString(a_name));
		if (!variable) {
			return false;
		}

		const auto structureLock = BSAutoSpinLock(structLock);
		return Impl::PackVariable(a_vm, *variable, std::forward<T>(a_value));
	}

	template <class T>
	auto Variable::Pack(IVirtualMachine& a_vm, T&& a_value) -> bool
		requires(BSScript::ValidateParameter<std::remove_reference_t<T>>())
	{
		return Impl::PackVariable(a_vm, *this, std::forward<T>(a_value));
	}

	template <class T>
	auto Variable::Unpack(IVirtualMachine& a_vm) const -> std::optional<std::remove_cv_t<T>>
		requires(BSScript::ValidateParameter<T>())
	{
		return Impl::UnpackVariable<T>(a_vm, *this);
	}
}

#define RE_BASIC_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, a_taskletCallable, a_terminateOnFailure) \
	a_vm.BindNativeFunction(a_scriptName, #a_func##sv, a_func, a_taskletCallable, a_terminateOnFailure)

#define RE_BASIC_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func, a_taskletCallable, a_terminateOnFailure) \
	a_vm.BindNativeLatentFunction(a_scriptName, #a_func##sv, a_func, a_taskletCallable, a_terminateOnFailure)

#define RE_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func)                 \
	RE_BASIC_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, false, false)

#define RE_REGISTER_VM_FUNCTION_ASYNC(a_vm, a_scriptName, a_func)          \
	RE_BASIC_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, true, false)

#define RE_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func)                 \
	RE_BASIC_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func, false, false)

#define RE_REGISTER_VM_FUNCTION_LATENT_ASYNC(a_vm, a_scriptName, a_func)          \
	RE_BASIC_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func, true, false)

#define RE_REGISTER_VM_FUNCTION_OR_FAIL(a_vm, a_scriptName, a_func)        \
	RE_BASIC_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, false, true)

#define RE_REGISTER_VM_FUNCTION_ASYNC_OR_FAIL(a_vm, a_scriptName, a_func) \
	RE_BASIC_REGISTER_VM_FUNCTION(a_vm, a_scriptName, a_func, true, true)

#define RE_REGISTER_VM_FUNCTION_LATENT_OR_FAIL(a_vm, a_scriptName, a_func)        \
	RE_BASIC_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func, false, true)

#define RE_REGISTER_VM_FUNCTION_LATENT_ASYNC_OR_FAIL(a_vm, a_scriptName, a_func) \
	RE_BASIC_REGISTER_VM_FUNCTION_LATENT(a_vm, a_scriptName, a_func, true, true)
