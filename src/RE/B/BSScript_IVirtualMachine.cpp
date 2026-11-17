#include "RE/B/BSScript_IVirtualMachine.hpp"

#include "RE/B/BSScriptUtility_StackErrorMessage.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_LogSeverity.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectBindPolicy.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/F/FormType.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"

namespace RE::BSScript
{
	auto IVirtualMachine::IsInstanceOf(const BSFixedString& a_childScriptName, const BSFixedString& a_parentScriptName)
		-> bool
	{
		if (a_childScriptName.empty() || a_parentScriptName.empty()) {
			return false;
		}

		auto childTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_childScriptName, childTypeInfo) || !childTypeInfo) {
			return false;
		}

		return IsInstanceOf(childTypeInfo, a_parentScriptName);
	}

	auto IVirtualMachine::IsInstanceOf(
		const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
		const BSFixedString& a_parentScriptName) -> bool
	{
		if (!a_childTypeInfo || a_parentScriptName.empty()) {
			return false;
		}

		auto parentTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_parentScriptName, parentTypeInfo) || !parentTypeInfo) {
			return false;
		}

		return IsInstanceOf(a_childTypeInfo, parentTypeInfo);
	}

	auto IVirtualMachine::IsInstanceOf(
		const BSFixedString& a_childScriptName,
		const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) -> bool
	{
		if (!a_parentTypeInfo || a_childScriptName.empty()) {
			return false;
		}

		auto childTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_childScriptName, childTypeInfo) || !childTypeInfo) {
			return false;
		}

		return IsInstanceOf(childTypeInfo, a_parentTypeInfo);
	}

	auto IVirtualMachine::IsInstanceOf(
		const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
		const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) -> bool
	{
		if (!a_childTypeInfo || !a_parentTypeInfo) {
			return false;
		}

		return a_childTypeInfo->IsChildOf(a_parentTypeInfo);
	}

	auto IVirtualMachine::IsInstanceOf(FormType a_formType, const BSFixedString& a_parentScriptName) -> bool
	{
		if (a_parentScriptName.empty()) {
			return false;
		}

		auto childTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_formType, childTypeInfo) || !childTypeInfo) {
			return false;
		}

		return IsInstanceOf(childTypeInfo, a_parentScriptName);
	}

	auto IVirtualMachine::IsInstanceOf(FormType a_formType, const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo)
		-> bool
	{
		if (!a_parentTypeInfo) {
			return false;
		}

		auto childTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_formType, childTypeInfo) || !childTypeInfo) {
			return false;
		}

		return IsInstanceOf(childTypeInfo, a_parentTypeInfo);
	}

	auto IVirtualMachine::GetFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
		-> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetFunction(objectTypeInfo, a_funcName);
	}

	auto IVirtualMachine::GetFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetFunction(objectTypeInfo, a_funcName, a_stateName);
	}

	auto IVirtualMachine::GetFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = a_objectTypeInfo->GetFunctionInfoByName(a_funcName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = a_objectTypeInfo->GetFunctionInfoByName(a_funcName, a_stateName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetMemberFunction(const BSTSmartPointer<Object>& a_object, const BSFixedString& a_funcName)
		-> BSTSmartPointer<IFunction>
	{
		if (!a_object) {
			return nullptr;
		}

		return GetMemberFunction(a_object, a_funcName, a_object->GetCurrentState());
	}

	auto IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<Object>& a_object,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>
	{
		if (!a_object) {
			return nullptr;
		}

		const auto objectTypeInfo = a_object->GetTypeInfo();
		if (!objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = objectTypeInfo->GetMemberFunctionInfoByName(a_funcName, a_stateName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetMemberFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
		-> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetMemberFunction(objectTypeInfo, a_funcName);
	}

	auto IVirtualMachine::GetMemberFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetMemberFunction(objectTypeInfo, a_funcName, a_stateName);
	}

	auto IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = a_objectTypeInfo->GetMemberFunctionInfoByName(a_funcName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = a_objectTypeInfo->GetMemberFunctionInfoByName(a_funcName, a_stateName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetStaticFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
		-> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetStaticFunction(objectTypeInfo, a_funcName);
	}

	auto IVirtualMachine::GetStaticFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* funcInfo = a_objectTypeInfo->GetStaticFunctionInfoByName(a_funcName);
		if (!funcInfo) {
			return nullptr;
		}

		return funcInfo->func;
	}

	auto IVirtualMachine::GetGetterFunction(const BSFixedString& a_scriptName, const BSFixedString& a_propertyName)
		-> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetGetterFunction(objectTypeInfo, a_propertyName);
	}

	auto IVirtualMachine::GetGetterFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_propertyName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* propInfo = a_objectTypeInfo->GetPropertyInfoByName(a_propertyName);
		if (!propInfo) {
			return nullptr;
		}

		return propInfo->info.getFunction;
	}

	auto IVirtualMachine::GetSetterFunction(const BSFixedString& a_scriptName, const BSFixedString& a_propertyName)
		-> BSTSmartPointer<IFunction>
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetSetterFunction(objectTypeInfo, a_propertyName);
	}

	auto IVirtualMachine::GetSetterFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_propertyName) -> BSTSmartPointer<IFunction>
	{
		if (!a_objectTypeInfo) {
			return nullptr;
		}

		const auto* propInfo = a_objectTypeInfo->GetPropertyInfoByName(a_propertyName);
		if (!propInfo) {
			return nullptr;
		}

		return propInfo->info.setFunction;
	}

	auto IVirtualMachine::GetScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) const -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = false;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		return FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, a_outObject, EXACT_TYPE);
	}

	auto IVirtualMachine::GetScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) const -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = true;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		return FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, a_outObject, EXACT_TYPE);
	}

	auto IVirtualMachine::GetOrCreateScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = false;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		auto object = BSTSmartPointer<Object>();
		if (FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, object, EXACT_TYPE)) {
			a_outObject = std::move(object);
			return true;
		}

		if (!CreateObject(a_scriptName, object)) {
			a_outObject = nullptr;
			return false;
		}

		const auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	auto IVirtualMachine::GetOrCreateScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		const REX::NotNull<std::move_only_function<BSTScrapHashMap<BSFixedString, Variable>() const>>&
			a_propertiesFactory,
		BSTSmartPointer<Object>& a_outObject) -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = false;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		auto object = BSTSmartPointer<Object>();
		if (FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, object, EXACT_TYPE)) {
			a_outObject = std::move(object);
			return true;
		}

		const auto properties = std::invoke(a_propertiesFactory.get());
		if (!CreateObject(a_scriptName, properties, object)) {
			a_outObject = nullptr;
			return false;
		}

		const auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	auto IVirtualMachine::GetOrCreateScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = true;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		auto object = BSTSmartPointer<Object>();
		if (FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, object, EXACT_TYPE)) {
			a_outObject = std::move(object);
			return true;
		}

		if (!CreateObject(a_scriptName, object)) {
			a_outObject = nullptr;
			return false;
		}

		const auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	auto IVirtualMachine::GetOrCreateScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		const REX::NotNull<std::move_only_function<BSTScrapHashMap<BSFixedString, Variable>() const>>&
			a_propertiesFactory,
		BSTSmartPointer<Object>& a_outObject) -> bool
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = true;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		auto object = BSTSmartPointer<Object>();
		if (FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, object, EXACT_TYPE)) {
			a_outObject = std::move(object);
			return true;
		}

		const auto properties = std::invoke(a_propertiesFactory.get());
		if (!CreateObject(a_scriptName, properties, object)) {
			a_outObject = nullptr;
			return false;
		}

		const auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	auto IVirtualMachine::GetScriptName(const BSTSmartPointer<Object>& a_object, BSFixedString& a_outScriptName) -> bool
	{
		if (!a_object) {
			a_outScriptName.clear();
			return false;
		}

		const auto objectTypeInfo = a_object->GetTypeInfo();
		if (!objectTypeInfo) {
			a_outScriptName.clear();
			return false;
		}

		a_outScriptName = objectTypeInfo->GetName();
		return true;
	}

	auto IVirtualMachine::GetScriptName(FormType a_formType, BSFixedString& a_outScriptName) -> bool
	{
		auto objectTypeInfo = BSTSmartPointer<BSScript::ObjectTypeInfo>();
		if (!GetScriptObjectType(a_formType, objectTypeInfo) || !objectTypeInfo) {
			a_outScriptName.clear();
			return false;
		}

		a_outScriptName = objectTypeInfo->GetName();
		return true;
	}

	void IVirtualMachine::PostMessage(REX::ZStringView a_message, StackID a_stackID, LogSeverity a_severity) const
	{
		// The implementation of `IVirtualMachine::PostCachedErrorToLogger` wraps the error message in another
		// `ICachedErrorMessage`, so the error logger is used directly instead, to be able to access the original error
		// message in `LogEvent`.

		const auto stackErrorMessage = StackErrorMessage(a_message, a_stackID);

		auto& errorLogger = GetErrorLogger();
		errorLogger.PostCachedError(stackErrorMessage, a_severity);
	}
}
