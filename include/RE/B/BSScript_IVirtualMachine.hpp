#pragma once

#include "RE/B/BSContainer_ForEachResult.hpp"
#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSIntrusiveRefCounted.hpp"
#include "RE/B/BSScriptUtil_Concepts.hpp"
#include "RE/B/BSScriptUtil_NativeFunction.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_ICachedErrorMessage.hpp"
#include "RE/B/BSScript_TypeInfo.hpp"
#include "RE/B/BSTArray.hpp"
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
	class Array;
	class BoundScript;
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

	class __declspec(novtable) IVirtualMachine
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IVirtualMachine };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IVirtualMachine };

		virtual ~IVirtualMachine() = default; // 00

		// add
		virtual void SetLoader(ILoader* a_newLoader) = 0;																																																																			 // 01
		virtual void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) = 0;																																																												 // 02
		virtual void Update(REX::Float32 a_updateBudget) = 0;																																																																		 // 03
		virtual void UpdateTasklets(REX::Float32 a_updateBudget) = 0;																																																																 // 04
		virtual void SetOverstressed(bool a_overstressed) = 0;																																																																		 // 05
		virtual bool IsCompletelyFrozen() const = 0;																																																																				 // 06
		virtual bool RegisterObjectType(FormType a_typeID, const char* a_scriptName) = 0;																																																											 // 07
		virtual bool GetScriptObjectType(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) = 0;																																																					 // 09
		virtual bool GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) = 0;																																																		 // 08
		virtual bool GetScriptObjectTypeNoLoad(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) const = 0;																																																		 // 0B
		virtual bool GetScriptObjectTypeNoLoad(const BSFixedString& a_scriptName, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) const = 0;																																														 // 0A
		virtual bool GetTypeIDForScriptObject(const BSFixedString& a_scriptName, FormType& a_typeID) const = 0;																																																						 // 0C
		virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_objectTypeList) const = 0;																																																							 // 0D
		virtual bool GetParentNativeType(const BSFixedString& a_childTypeName, BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) = 0;																																																 // 0E
		virtual bool TypeIsValid(const BSFixedString& a_scriptName) = 0;																																																															 // 0F
		virtual bool ReloadType(const char* a_scriptName) = 0;																																																																		 // 10
		virtual void TasksToJobs(JobList& a_jobList) = 0;																																																																			 // 11
		virtual void CalculateFullReloadList(const BSTSet<BSFixedString>& a_scriptSet, BSTScrapObjectArena<BSFixedString, 32>& a_scriptList) const = 0;																																												 // 12
		virtual bool GetScriptStructType(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) = 0;																																																	 // 13
		virtual bool GetScriptStructTypeNoLoad(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) const = 0;																																														 // 14
		virtual bool GetChildStructTypes(const BSFixedString& a_parentObjectName, BSTScrapObjectArena<BSFixedString, 32>& a_structTypes) const = 0;																																													 // 15
		virtual bool CreateObject(const BSFixedString& a_scriptName, BSTSmartPointer<Object>& a_newObject) = 0;																																																						 // 16
		virtual bool CreateObject(const BSFixedString& a_scriptName, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, BSTSmartPointer<Object>& a_newObject) = 0;																																						 // 17 -- this is intended; not the right order, but the compiler appears to swap the two for some reason
		virtual bool CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_newStruct) = 0;																																																					 // 18
		virtual bool CreateArray(TypeInfo::RawType a_elementType, const BSFixedString& a_elementObjectTypeName, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																																				 // 1A
		virtual bool CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																																																		 // 19
		virtual bool BindNativeMethod(IFunction* a_func) = 0;																																																																		 // 1B
		virtual void SetCallableFromTasklets(const char* a_scriptName, const char* a_funcName, bool a_taskletCallable) = 0;																																																			 // 1D
		virtual void SetCallableFromTasklets(const char* a_scriptName, const char* a_stateName, const char* a_funcName, bool a_taskletCallable) = 0;																																												 // 1C
		virtual void ForEachBoundObject(ObjectHandle a_objectHandle, const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) = 0;																																												 // 1E
		virtual bool FindBoundObject(ObjectHandle a_objectHandle, const char* a_scriptName, bool a_allowConst, BSTSmartPointer<Object>& a_attachedObject, bool a_exactType) const = 0;																																				 // 1F
		virtual void MoveBoundObjects(ObjectHandle a_sourceObjectHandle, ObjectHandle a_targetObjectHandle) = 0;																																																					 // 20
		virtual void ResetAllBoundObjects(ObjectHandle a_objectHandle) = 0;																																																															 // 21
		virtual bool CastObject(const BSTSmartPointer<Object>& a_sourceObject, const BSTSmartPointer<ObjectTypeInfo>& a_targetType, BSTSmartPointer<Object>& a_castedObject) = 0;																																					 // 22
		virtual bool SetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propertyName, const Variable& a_newValue, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;																															 // 23
		virtual bool GetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propertyName, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;																																						 // 24
		virtual bool GetVariableValue(ObjectHandle a_objectHandle, const BSFixedString& a_scriptName, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																											 // 26
		virtual bool GetVariableValue(const BSTSmartPointer<Object>& a_object, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																																 // 25
		virtual bool HandleImplementsEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName) const = 0;																																																				 // 27
		virtual bool AddEventRelay(ObjectHandle a_sourceObjectHandle, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_targetObject) = 0;																																											 // 28
		virtual void RemoveEventRelay(ObjectHandle a_sourceObjectHandle, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_targetObject) = 0;																																										 // 29
		virtual void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_targetObject) = 0;																																																										 // 2A
		virtual void SendEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filterFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0; // 2B
		virtual bool DispatchStaticCall(const BSFixedString& a_scriptName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;																		 // 2C
		virtual bool DispatchMethodCall(ObjectHandle a_objectHandle, const BSFixedString& a_scriptName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;											 // 2E
		virtual bool DispatchMethodCall(const BSTSmartPointer<Object>& a_self, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;																	 // 2D
		virtual bool DispatchUnboundMethodCall(ObjectHandle a_objectHandle, const BSTSmartPointer<BoundScript>& a_script, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) = 0;						 // 2F
		virtual bool IsWaitingOnLatent(StackID a_stackID) const = 0;																																																																 // 30
		virtual void ReturnFromLatent(StackID a_stackID, const Variable& a_result) = 0;																																																												 // 31
		virtual ErrorLogger& GetErrorLogger() const = 0;																																																																			 // 32
		virtual const IObjectHandlePolicy& GetObjectHandlePolicy() const = 0;																																																														 // 34
		virtual IObjectHandlePolicy& GetObjectHandlePolicy() = 0;																																																																	 // 33
		virtual const ObjectBindPolicy& GetObjectBindPolicy() const = 0;																																																															 // 36
		virtual ObjectBindPolicy& GetObjectBindPolicy() = 0;																																																																		 // 35
		virtual ISavePatcherInterface& GetSavePatcherInterface() = 0;																																																																 // 37
		virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) = 0;																																																													 // 38
		virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) = 0;																																																												 // 39
		virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) = 0;																																																												 // 3A
		virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) = 0;																																																											 // 3B
		virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, ErrorLogger::Severity a_severity = ErrorLogger::Severity::kError) const = 0;																																								 // 3D
		virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, StackID a_stackID, ErrorLogger::Severity a_severity = ErrorLogger::Severity::kError) const = 0;																																				 // 3C

		[[nodiscard]] bool IsInstanceOf(
			const BSFixedString& a_childScriptName,
			const BSFixedString& a_parentScriptName);

		[[nodiscard]] bool IsInstanceOf(
			const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
			const BSFixedString& a_parentScriptName);

		[[nodiscard]] bool IsInstanceOf(
			const BSFixedString& a_childScriptName,
			const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo);

		[[nodiscard]] static bool IsInstanceOf(
			const BSTSmartPointer<ObjectTypeInfo>& a_childTypeInfo,
			const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo);

		[[nodiscard]] bool IsInstanceOf(
			FormType a_formType,
			const BSFixedString& a_parentScriptName);

		[[nodiscard]] bool IsInstanceOf(
			FormType a_formType,
			const BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo);

		[[nodiscard]] BSTSmartPointer<IFunction> GetFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetMemberFunction(
			const BSTSmartPointer<Object>& a_object,
			const BSFixedString& a_funcName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetMemberFunction(
			const BSTSmartPointer<Object>& a_object,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetMemberFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetMemberFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetMemberFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetMemberFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName,
			const BSFixedString& a_stateName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetStaticFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_funcName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetGetterFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_propertyName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetGetterFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_propertyName);

		[[nodiscard]] BSTSmartPointer<IFunction> GetSetterFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_propertyName);

		[[nodiscard]] static BSTSmartPointer<IFunction> GetSetterFunction(
			const BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo,
			const BSFixedString& a_propertyName);

		template <class... Args>
		bool InvokeMemberFunction(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			Args&&... a_args)
			requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

		template <class... Args>
		bool InvokeStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			Args&&... a_args)
			requires((BSScript::ValidateParameter<std::remove_reference_t<Args>>() && ...));

		inline bool InvokeAppliedMemberFunction(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			std::span<const Variable> a_args);

		inline bool InvokeAppliedMemberFunction(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			BSScrapArray<Variable>&& a_args);

		inline bool InvokeAppliedStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			std::span<const Variable> a_args);

		inline bool InvokeAppliedStaticFunction(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor,
			BSScrapArray<Variable>&& a_args);

		void ReturnLatentFunction(
			StackID a_stackID);

		template <class T>
		void ReturnLatentFunction(
			StackID a_stackID,
			T&& a_result)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		LatentResult<void> ReturnLatentResult(
			StackID a_stackID);

		template <class T>
		LatentResult<std::remove_reference_t<T>> ReturnLatentResult(
			StackID a_stackID,
			T&& a_result)
			requires(BSScript::ValidateParameter<std::remove_reference_t<T>>());

		template <class T>
		bool BindNativeFunction(
			REX::zstring_view a_scriptName,
			REX::zstring_view a_funcName,
			const T& a_func,
			bool a_taskletCallable)
			requires(requires { NativeFunction(a_scriptName, a_funcName, a_func); });

		template <class T>
		bool BindNativeLatentFunction(
			REX::zstring_view a_scriptName,
			REX::zstring_view a_funcName,
			const T& a_func,
			bool a_taskletCallable)
			requires(requires { NativeLatentFunction(a_scriptName, a_funcName, a_func); });

		bool GetScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) const;

		bool GetScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject) const;

		bool GetOrCreateScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject);

		bool GetOrCreateScriptObject(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			const REX::NotNull<std::function<BSTScrapHashMap<BSFixedString, Variable>()>>& a_propertiesFactory,
			BSTSmartPointer<Object>& a_outObject);

		bool GetOrCreateScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			BSTSmartPointer<Object>& a_outObject);

		bool GetOrCreateScriptObjectExact(
			const BSFixedString& a_scriptName,
			ObjectHandle a_objectHandle,
			const REX::NotNull<std::function<BSTScrapHashMap<BSFixedString, Variable>()>>& a_propertiesFactory,
			BSTSmartPointer<Object>& a_outObject);

		static bool GetScriptName(
			const BSTSmartPointer<Object>& a_object,
			BSFixedString& a_outScriptName);

		bool GetScriptName(
			FormType a_formType,
			BSFixedString& a_outScriptName);

		void PostMessage(
			REX::zstring_view a_message,
			StackID a_stackID,
			ErrorLogger::Severity a_severity) const;

		template <class... Args>
		void PostMessage(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			ErrorLogger::Severity a_severity,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		void PostInfo(
			REX::zstring_view a_message,
			StackID a_stackID) const;

		template <class... Args>
		void PostInfo(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		void PostWarning(
			REX::zstring_view a_message,
			StackID a_stackID) const;

		template <class... Args>
		void PostWarning(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		void PostError(
			REX::zstring_view a_message,
			StackID a_stackID) const;

		template <class... Args>
		void PostError(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));

		void PostFatal(
			REX::zstring_view a_message,
			StackID a_stackID) const;

		template <class... Args>
		void PostFatal(
			REX::FormatString<Args...> a_format,
			StackID a_stackID,
			Args&&... a_args) const
			requires((REX::formattable<Args, char> && ...));
	};
	static_assert(sizeof(IVirtualMachine) == 0x10);
}
