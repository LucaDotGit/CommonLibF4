#include "RE/B/BSScript_IVirtualMachine.hpp"

#include "RE//G/GameScript_HandlePolicy.hpp"
#include "RE/B/BSScriptUtil_CachedErrorMessage.hpp"
#include "RE/B/BSScriptUtil_InternalLogEvent.hpp"
#include "RE/B/BSScript_IComplexType.hpp"
#include "RE/B/BSScript_IFunction.hpp"
#include "RE/B/BSScript_Object.hpp"
#include "RE/B/BSScript_ObjectBindPolicy.hpp"
#include "RE/B/BSScript_ObjectTypeInfo.hpp"
#include "RE/B/BSScript_StructTypeInfo.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSScript_Variable.hpp"
#include "RE/F/FormType.hpp"

namespace RE::BSScript
{
	bool IVirtualMachine::IsInstanceOf(
		const BSFixedString& a_childScriptName,
		const BSFixedString& a_parentScriptName)
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

	bool IVirtualMachine::IsInstanceOf(
		const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
		const BSFixedString& a_parentScriptName)
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

	bool IVirtualMachine::IsInstanceOf(
		const BSFixedString& a_childScriptName,
		const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo)
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

	bool IVirtualMachine::IsInstanceOf(
		const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
		const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo)
	{
		if (!a_childTypeInfo || !a_parentTypeInfo) {
			return false;
		}

		return a_childTypeInfo->IsChildOf(a_parentTypeInfo);
	}

	bool IVirtualMachine::IsInstanceOf(
		FormType a_formType,
		const BSFixedString& a_parentScriptName)
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

	bool IVirtualMachine::IsInstanceOf(
		FormType a_formType,
		const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetFunction(objectTypeInfo, a_funcName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetFunction(objectTypeInfo, a_funcName, a_stateName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<Object>& a_object,
		const BSFixedString& a_funcName)
	{
		if (!a_object) {
			return nullptr;
		}

		return GetMemberFunction(a_object, a_funcName, a_object->GetCurrentState());
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<Object>& a_object,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetMemberFunction(objectTypeInfo, a_funcName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetMemberFunction(objectTypeInfo, a_funcName, a_stateName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetMemberFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName,
		const BSFixedString& a_stateName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetStaticFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_funcName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetStaticFunction(objectTypeInfo, a_funcName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetStaticFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_funcName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetGetterFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_propertyName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetGetterFunction(objectTypeInfo, a_propertyName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetGetterFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_propertyName)
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

	BSTSmartPointer<IFunction> IVirtualMachine::GetSetterFunction(
		const BSFixedString& a_scriptName,
		const BSFixedString& a_propertyName)
	{
		auto objectTypeInfo = BSTSmartPointer<ObjectTypeInfo>();
		if (!GetScriptObjectType(a_scriptName, objectTypeInfo) || !objectTypeInfo) {
			return nullptr;
		}

		return GetSetterFunction(objectTypeInfo, a_propertyName);
	}

	BSTSmartPointer<IFunction> IVirtualMachine::GetSetterFunction(
		const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
		const BSFixedString& a_propertyName)
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

	bool IVirtualMachine::GetScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) const
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = false;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		return FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, a_outObject, EXACT_TYPE);
	}

	bool IVirtualMachine::GetScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject) const
	{
		constexpr auto ALLOW_CONST = false;
		constexpr auto EXACT_TYPE = true;

		if (a_objectHandle == GameScript::HandlePolicy::EMPTY_HANDLE || a_scriptName.empty()) {
			a_outObject = nullptr;
			return false;
		}

		return FindBoundObject(a_objectHandle, a_scriptName.data(), ALLOW_CONST, a_outObject, EXACT_TYPE);
	}

	bool IVirtualMachine::GetOrCreateScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject)
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

		auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	bool IVirtualMachine::GetOrCreateScriptObject(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		const REX::NotNull<std::function<BSTScrapHashMap<BSFixedString, Variable>()>>& a_propertiesFactory,
		BSTSmartPointer<Object>& a_outObject)
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

		auto properties = std::invoke(*a_propertiesFactory);
		if (!CreateObject(a_scriptName, properties, object)) {
			a_outObject = nullptr;
			return false;
		}

		auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	bool IVirtualMachine::GetOrCreateScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		BSTSmartPointer<Object>& a_outObject)
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

		auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	bool IVirtualMachine::GetOrCreateScriptObjectExact(
		const BSFixedString& a_scriptName,
		ObjectHandle a_objectHandle,
		const REX::NotNull<std::function<BSTScrapHashMap<BSFixedString, Variable>()>>& a_propertiesFactory,
		BSTSmartPointer<Object>& a_outObject)
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

		auto properties = std::invoke(*a_propertiesFactory);
		if (!CreateObject(a_scriptName, properties, object)) {
			a_outObject = nullptr;
			return false;
		}

		auto& bindPolicy = GetObjectBindPolicy();
		bindPolicy.BindObject(object, a_objectHandle);

		a_outObject = std::move(object);
		return true;
	}

	bool IVirtualMachine::GetScriptName(
		const BSTSmartPointer<Object>& a_object,
		BSFixedString& a_outScriptName)
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

	bool IVirtualMachine::GetScriptName(
		FormType a_formType,
		BSFixedString& a_outScriptName)
	{
		auto objectTypeInfo = BSTSmartPointer<BSScript::ObjectTypeInfo>();
		if (!GetScriptObjectType(a_formType, objectTypeInfo) || !objectTypeInfo) {
			a_outScriptName.clear();
			return false;
		}

		a_outScriptName = objectTypeInfo->GetName();
		return true;
	}

	void IVirtualMachine::PostMessage(
		REX::zstring_view a_message,
		StackID a_stackID,
		ErrorLogger::Severity a_severity) const
	{
		{
			const auto internalLogEvent = Impl::InternalLogEvent{
				.message = a_message,
				.severity = a_severity,
				.stackID = a_stackID
			};

			Impl::InternalLogEventSource::GetSingleton()->Notify(internalLogEvent);
		}

		const auto errorFunctor = Impl::CachedErrorMessage(a_message);
		PostCachedErrorToLogger(errorFunctor, a_stackID, a_severity);
	}

	void IVirtualMachine::PostInfo(
		REX::zstring_view a_message,
		StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, ErrorLogger::Severity::kInfo);
	}

	void IVirtualMachine::PostWarning(
		REX::zstring_view a_message,
		StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, ErrorLogger::Severity::kWarning);
	}

	void IVirtualMachine::PostError(
		REX::zstring_view a_message,
		StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, ErrorLogger::Severity::kError);
	}

	void IVirtualMachine::PostFatal(
		REX::zstring_view a_message,
		StackID a_stackID) const
	{
		PostMessage(a_message, a_stackID, ErrorLogger::Severity::kFatal);
	}
}
