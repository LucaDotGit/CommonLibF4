#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScriptUtility_Concepts.hpp"
#include "RE/B/BSScriptUtility_NativeFunction.hpp"
#include "RE/B/BSScript_ICachedErrorMessage.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTThreadScrapFunction.hpp"

namespace RE
{
	enum class FormType : std::int32_t;
}

namespace RE::BSScript
{
	enum class LogSeverity : std::int32_t;

	class Array;
	class BoundScript;
	class ErrorLogger;
	class IFunction;
	class ILoader;
	class IObjectHandlePolicy;
	class ISavePatcherInterface;
	class IStackCallbackFunctor;
	class ITypeLinkedCallback;
	class JobList;
	class LogEvent;
	class Object;
	class ObjectBindPolicy;
	class ObjectTypeInfo;
	class StatsEvent;
	class Struct;
	class StructTypeInfo;
	class TypeInfo;
	class Variable;

	class __declspec(novtable) IVirtualMachine : public BSIntrusiveRefCounted // 0x08
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__IVirtualMachine;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__IVirtualMachine;

		virtual ~IVirtualMachine() = default; // 0x00

		// add
		virtual void SetLoader(ILoader* a_newLoader) = 0;										  // 0x01
		virtual void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) = 0;			  // 0x02
		virtual void Update(REX::Float32 a_updateBudget) = 0;									  // 0x03
		virtual void UpdateTasklets(REX::Float32 a_updateBudget) = 0;							  // 0x04
		virtual void SetOverstressed(bool a_overstressed) = 0;									  // 0x05
		virtual auto IsCompletelyFrozen() const -> bool = 0;									  // 0x06
		virtual auto RegisterObjectType(FormType a_typeID, const char* a_scriptName) -> bool = 0; // 0x07
		virtual auto GetScriptObjectType(
			FormType a_typeID,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo) -> bool = 0; // 0x09
		virtual auto GetScriptObjectType(
			const BSFixedString& a_name,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo) -> bool = 0; // 0x08
		virtual auto GetScriptObjectTypeNoLoad(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo)
			const -> bool = 0; // 0x0B
		virtual auto GetScriptObjectTypeNoLoad(
			const BSFixedString& a_scriptName,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo) const -> bool = 0; // 0x0A
		virtual auto GetTypeIDForScriptObject(const BSFixedString& a_scriptName, FormType& a_outTypeID) const
			-> bool = 0;																					  // 0x0C
		virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_outObjectTypeInfo) const = 0; // 0x0D
		virtual auto GetParentNativeType(
			const BSFixedString& a_childTypeName,
			BSTSmartPointer<ObjectTypeInfo>& a_outParentTypeInfo) -> bool = 0;	 // 0x0E
		virtual auto TypeIsValid(const BSFixedString& a_scriptName) -> bool = 0; // 0x0F
		virtual auto ReloadType(const char* a_scriptName) -> bool = 0;			 // 0x10
		virtual void TasksToJobs(JobList& a_jobList) = 0;						 // 0x11
		virtual void CalculateFullReloadList(
			const BSTSet<BSFixedString>& a_scriptSet,
			BSTScrapObjectArena<BSFixedString, 0x20>& a_outScriptList) const = 0; // 0x12
		virtual auto GetScriptStructType(
			const BSFixedString& a_structTypeName,
			BSTSmartPointer<StructTypeInfo>& a_outStructType) -> bool = 0; // 0x13
		virtual auto GetScriptStructTypeNoLoad(
			const BSFixedString& a_structTypeName,
			BSTSmartPointer<StructTypeInfo>& a_outStructType) const -> bool = 0; // 0x14
		virtual auto GetChildStructTypes(
			const BSFixedString& a_parentObjectName,
			BSTScrapObjectArena<BSFixedString, 0x20>& a_outStructTypes) const -> bool = 0; // 0x15
		virtual auto CreateObject(
			const BSFixedString& a_scriptName,
			BSTSmartPointer<Object>& a_outNewObject) -> bool = 0; // 0x16
		virtual auto CreateObject(
			const BSFixedString& a_scriptName,
			const BSTScrapHashMap<BSFixedString, Variable>& a_properties,
			BSTSmartPointer<Object>& a_outNewObject)
			-> bool = 0; // 0x17 - this is intended; not the right order, but the
						 // compiler appears to swap the two for some reason
		virtual auto CreateStruct(
			const BSFixedString& a_structTypeName,
			BSTSmartPointer<Struct>& a_outNewStruct) -> bool = 0; // 0x18
		virtual auto CreateArray(
			TypeInfo::RawType a_elementType,
			const BSFixedString& a_elementObjectTypeName,
			std::uint32_t a_elementCount,
			BSTSmartPointer<Array>& a_outNewArray) -> bool = 0; // 0x1A
		virtual auto CreateArray(
			const TypeInfo& a_type,
			std::uint32_t a_elementCount,
			BSTSmartPointer<Array>& a_outNewArray) -> bool = 0;		  // 0x19
		virtual auto BindNativeMethod(IFunction* a_func) -> bool = 0; // 0x1B
		virtual void SetCallableFromTasklets(
			const char* a_scriptName,
			const char* a_funcName,
			bool a_taskletCallable) = 0; // 0x1D
		virtual void SetCallableFromTasklets(
			const char* a_scriptName,
			const char* a_stateName,
			const char* a_funcName,
			bool a_taskletCallable) = 0; // 0x1C
		virtual void ForEachBoundObject(
			ObjectHandle a_objectHandle,
			const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) = 0; // 0x1E
		virtual auto FindBoundObject(
			ObjectHandle a_objectHandle,
			const char* a_scriptName,
			bool a_allowConst,
			BSTSmartPointer<Object>& a_outAttachedObject,
			bool a_exactType) const -> bool = 0;																 // 0x1F
		virtual void MoveBoundObjects(ObjectHandle a_sourceObjectHandle, ObjectHandle a_targetObjectHandle) = 0; // 0x20
		virtual void ResetAllBoundObjects(ObjectHandle a_objectHandle) = 0;										 // 0x21
		virtual auto CastObject(
			const BSTSmartPointer<Object>& a_sourceObject,
			const BSTSmartPointer<ObjectTypeInfo>& a_targetType,
			BSTSmartPointer<Object>& a_castedObject) -> bool = 0; // 0x22
		virtual auto SetPropertyValue(
			const BSTSmartPointer<Object>& a_self,
			const char* a_propertyName,
			const Variable& a_newValue,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x23
		virtual auto GetPropertyValue(
			const BSTSmartPointer<Object>& a_self,
			const char* a_propertyName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x24
		virtual auto GetVariableValue(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_scriptName,
			std::uint32_t a_varIndex,
			Variable& a_outVar) const -> bool = 0; // 0x26
		virtual auto GetVariableValue(
			const BSTSmartPointer<Object>& a_object,
			std::uint32_t a_varIndex,
			Variable& a_outVar) const -> bool = 0; // 0x25
		virtual auto HandleImplementsEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName) const
			-> bool = 0; // 0x27
		virtual auto AddEventRelay(
			ObjectHandle a_sourceObjectHandle,
			const BSFixedString& a_eventName,
			const BSTSmartPointer<Object>& a_targetObject) -> bool = 0; // 0x28
		virtual void RemoveEventRelay(
			ObjectHandle a_sourceObjectHandle,
			const BSFixedString& a_eventName,
			const BSTSmartPointer<Object>& a_targetObject) = 0;								  // 0x29
		virtual void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_targetObject) = 0; // 0x2A
		virtual void SendEvent(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_eventName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filterFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0; // 0x2B
		virtual auto DispatchStaticCall(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x2C
		virtual auto DispatchMethodCall(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x2E
		virtual auto DispatchMethodCall(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x2D
		virtual auto DispatchUnboundMethodCall(
			ObjectHandle a_objectHandle,
			const BSTSmartPointer<BoundScript>& a_script,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool = 0; // 0x2F
		virtual auto IsWaitingOnLatent(StackID a_stackID) const -> bool = 0;			  // 0x30
		virtual void ReturnFromLatent(StackID a_stackID, const Variable& a_result) = 0;	  // 0x31
		virtual auto GetErrorLogger() const -> ErrorLogger& = 0;						  // 0x32
		virtual auto GetObjectHandlePolicy() const -> const IObjectHandlePolicy& = 0;	  // 0x34
		virtual auto GetObjectHandlePolicy() -> IObjectHandlePolicy& = 0;				  // 0x33
		virtual auto GetObjectBindPolicy() const -> const ObjectBindPolicy& = 0;		  // 0x36
		virtual auto GetObjectBindPolicy() -> ObjectBindPolicy& = 0;					  // 0x35
		virtual auto GetSavePatcherInterface() -> ISavePatcherInterface& = 0;			  // 0x37
		virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) = 0;		  // 0x38
		virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) = 0;	  // 0x39
		virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) = 0;	  // 0x3A
		virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) = 0;  // 0x3B
		virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, LogSeverity a_severity)
			const = 0; // 0x3D
		virtual void PostCachedErrorToLogger(
			const ICachedErrorMessage& a_errorFunctor,
			StackID a_stackID,
			LogSeverity a_severity) const = 0; // 0x3C

		[[nodiscard]]
		auto IsInstanceOf(const BSFixedString& a_childScriptName, const BSFixedString& a_parentScriptName) -> bool;

		[[nodiscard]]
		auto IsInstanceOf(
			const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
			const BSFixedString& a_parentScriptName) -> bool;

		[[nodiscard]]
		auto IsInstanceOf(
			const BSFixedString& a_childScriptName,
			const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) -> bool;

		[[nodiscard]]
		static auto IsInstanceOf(
			const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
			const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) -> bool;

		[[nodiscard]]
		auto IsInstanceOf(FormType a_formType, const BSFixedString& a_parentScriptName) -> bool;

		[[nodiscard]]
		auto IsInstanceOf(FormType a_formType, const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) -> bool;

		[[nodiscard]]
		auto GetFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetMemberFunction(const BSTSmartPointer<Object>& a_object, const BSFixedString& a_funcName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetMemberFunction(
			const BSTSmartPointer<Object>& a_object,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetMemberFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetMemberFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetMemberFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetMemberFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetStaticFunction(const BSFixedString& a_scriptName, const BSFixedString& a_funcName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetStaticFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetGetterFunction(const BSFixedString& a_scriptName, const BSFixedString& a_propertyName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetGetterFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_propertyName) -> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		auto GetSetterFunction(const BSFixedString& a_scriptName, const BSFixedString& a_propertyName)
			-> BSTSmartPointer<IFunction>;

		[[nodiscard]]
		static auto GetSetterFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_propertyName) -> BSTSmartPointer<IFunction>;

		auto GetScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) const -> bool;

		auto GetScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) const -> bool;

		auto GetOrCreateScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) -> bool;

		auto GetOrCreateScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			const REX::NotNull<std::move_only_function<BSTScrapHashMap<BSFixedString, Variable>() const>>&
				a_propertiesFactory,
			BSTSmartPointer<Object>& a_outObject) -> bool;

		auto GetOrCreateScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) -> bool;

		auto GetOrCreateScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			const REX::NotNull<std::move_only_function<BSTScrapHashMap<BSFixedString, Variable>() const>>&
				a_propertiesFactory,
			BSTSmartPointer<Object>& a_outObject) -> bool;

		static auto GetScriptName(const BSTSmartPointer<Object>& a_object, BSFixedString& a_outScriptName) -> bool;

		auto GetScriptName(FormType a_formType, BSFixedString& a_outScriptName) -> bool;

		template <class... Args>
		auto InvokeMemberFunction(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			Args&&... a_args) -> bool
			requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

		template <class... Args>
		auto InvokeStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			Args&&... a_args) -> bool
			requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

		inline auto InvokeAppliedMemberFunction(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			std::span<const Variable> a_args) -> bool;

		inline auto InvokeAppliedStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			std::span<const Variable> a_args) -> bool;

		inline void ReturnLatentFunction(StackID a_stackID);

		template <class T>
		void ReturnLatentFunction(StackID a_stackID, T&& a_result)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		inline auto ReturnLatentResult(StackID a_stackID) -> LatentResult<void>;

		template <class T>
		auto ReturnLatentResult(StackID a_stackID, T&& a_result) -> LatentResult<std::remove_reference_t<T>>
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		auto BindNativeFunction(
			REX::ZStringView a_scriptName,
			REX::ZStringView a_funcName,
			const T& a_func,
			bool a_taskletCallable,
			bool a_terminateOnFailure = false) -> bool
			requires(requires {
				NativeFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func);
			});

		template <class T>
		auto BindNativeLatentFunction(
			REX::ZStringView a_scriptName,
			REX::ZStringView a_funcName,
			const T& a_func,
			bool a_taskletCallable,
			bool a_terminateOnFailure = false) -> bool
			requires(requires {
				NativeLatentFunction(*this, BSFixedString(a_scriptName), BSFixedString(a_funcName), a_func);
			});

		void PostMessage(REX::ZStringView a_message, StackID a_stackID, LogSeverity a_severity) const;

		template <class... Args>
		void PostMessage(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			LogSeverity a_severity,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		inline void PostInfo(REX::ZStringView a_message, StackID a_stackID) const;

		template <class... Args>
		void PostInfo(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		inline void PostWarning(REX::ZStringView a_message, StackID a_stackID) const;

		template <class... Args>
		void PostWarning(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		inline void PostError(REX::ZStringView a_message, StackID a_stackID) const;

		template <class... Args>
		void PostError(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		inline void PostFatal(REX::ZStringView a_message, StackID a_stackID) const;

		template <class... Args>
		void PostFatal(REX::FormatString<Args...> a_format, StackID a_stackID, Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));
	};

	static_assert(sizeof(IVirtualMachine) == 0x10);
}
