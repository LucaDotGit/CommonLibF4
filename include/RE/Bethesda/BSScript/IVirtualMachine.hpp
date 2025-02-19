#pragma once

#include "RE/Bethesda/BSContainer.hpp"
#include "RE/Bethesda/BSFixedString.hpp"
#include "RE/Bethesda/BSLock.hpp"
#include "RE/Bethesda/BSScript/Array.hpp"
#include "RE/Bethesda/BSScript/ErrorLogger.hpp"
#include "RE/Bethesda/BSScript/ICachedErrorMessage.hpp"
#include "RE/Bethesda/BSScript/IFunction.hpp"
#include "RE/Bethesda/BSScript/ILoader.hpp"
#include "RE/Bethesda/BSScript/IObjectHandlePolicy.hpp"
#include "RE/Bethesda/BSScript/ISavePatcherInterface.hpp"
#include "RE/Bethesda/BSScript/IStackCallbackFunctor.hpp"
#include "RE/Bethesda/BSScript/Object.hpp"
#include "RE/Bethesda/BSScript/ObjectBindPolicy.hpp"
#include "RE/Bethesda/BSScript/ObjectTypeInfo.hpp"
#include "RE/Bethesda/BSScript/Struct.hpp"
#include "RE/Bethesda/BSScript/StructTypeInfo.hpp"
#include "RE/Bethesda/BSScript/TypeInfo.hpp"
#include "RE/Bethesda/BSScript/Variable.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTHashMap.hpp"
#include "RE/Bethesda/BSTObjectArena.hpp"
#include "RE/Bethesda/BSTSmartPointer.hpp"
#include "RE/Bethesda/BSTThreadScrapFunction.hpp"

namespace RE::BSScript
{
	class Array;
	class BoundScript; // stub
	class ErrorLogger;
	class ICachedErrorMessage;
	class IFunction;
	class ISavePatcherInterface;
	class IStackCallbackFunctor;
	class ITypeLinkedCallback; // stub
	class JobList;			   // stub
	class Object;
	class ObjectBindPolicy;
	class ObjectTypeInfo;
	class Struct;
	class StructTypeInfo;
	class TypeInfo;
	class Variable;

	struct ILoader;
	struct IObjectHandlePolicy;
	struct LogEvent;
	struct StatsEvent;

	namespace UnlinkedTypes
	{
		struct Object; // stub
	}

	class __declspec(novtable) IVirtualMachine
		: public BSIntrusiveRefCounted // 08
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__IVirtualMachine };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__IVirtualMachine };

		virtual ~IVirtualMachine() = default; // 00

		// add
		virtual void SetLoader(ILoader* a_newLoader) = 0;																																																													  // 01
		virtual void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) = 0;																																																						  // 02
		virtual void Update(float a_updateBudget) = 0;																																																														  // 03
		virtual void UpdateTasklets(float a_updateBudget) = 0;																																																												  // 04
		virtual void SetOverstressed(bool a_overstressed) = 0;																																																												  // 05
		virtual bool IsCompletelyFrozen() const = 0;																																																														  // 06
		virtual bool RegisterObjectType(VMTypeID a_typeID, const char* a_objectTypeName) = 0;																																																				  // 07
		virtual bool GetScriptObjectType(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;																																																  // 09
		virtual bool GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_objType) = 0;																																														  // 08
		virtual bool GetScriptObjectTypeNoLoad(VMTypeID a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;																																													  // 0B
		virtual bool GetScriptObjectTypeNoLoad(const BSFixedString& a_objectTypeName, BSTSmartPointer<ObjectTypeInfo>& a_objType) const = 0;																																								  // 0A
		virtual bool GetTypeIDForScriptObject(const BSFixedString& a_objectTypeName, VMTypeID& a_typeID) const = 0;																																															  // 0C
		virtual void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_objectTypeList) const = 0;																																																	  // 0D
		virtual bool GetParentNativeType(const BSFixedString& a_childTypeName, BSTSmartPointer<ObjectTypeInfo>& a_parentType) = 0;																																											  // 0E
		virtual bool TypeIsValid(const BSFixedString& a_objectTypeName) = 0;																																																								  // 0F
		virtual bool ReloadType(const char* a_objectTypeName) = 0;																																																											  // 10
		virtual void TasksToJobs(JobList& a_jobList) = 0;																																																													  // 11
		virtual void CalculateFullReloadList(const BSTSet<BSFixedString>& a_scriptSet, BSTObjectArena<BSFixedString>& a_scriptList) const = 0;																																								  // 12
		virtual bool GetScriptStructType(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) = 0;																																											  // 13
		virtual bool GetScriptStructTypeNoLoad(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) const = 0;																																								  // 14
		virtual bool GetChildStructTypes(const BSFixedString& a_parentObjectName, BSTObjectArena<BSFixedString>& a_structTypes) const = 0;																																									  // 15
		virtual bool CreateObject(const BSFixedString& a_objectTypeName, BSTSmartPointer<Object>& a_newObj) = 0;																																															  // 16
		virtual bool CreateObject(const BSFixedString& a_objectTypeName, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, BSTSmartPointer<Object>& a_newObj) = 0;																																  // 17 -- this is intended; not the right order, but the compiler appears to swap the two for some reason
		virtual bool CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_newStruct) = 0;																																															  // 18
		virtual bool CreateArray(TypeInfo::RawType a_elementType, const BSFixedString& a_elementObjectTypeName, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																														  // 1A
		virtual bool CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) = 0;																																												  // 19
		virtual bool BindNativeMethod(IFunction* a_function) = 0;																																																											  // 1B
		virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_functionName, bool a_taskletCallable) = 0;																																												  // 1D
		virtual void SetCallableFromTasklets(const char* a_objectName, const char* a_stateName, const char* a_functionName, bool a_taskletCallable) = 0;																																					  // 1C
		virtual void ForEachBoundObject(VMHandle a_objHandle, const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) = 0;																																							  // 1E
		virtual bool FindBoundObject(VMHandle a_objHandle, const char* a_objectTypeName, bool a_allowConst, BSTSmartPointer<Object>& a_attachedObj, bool a_exactMatch) const = 0;																															  // 1F
		virtual void MoveBoundObjects(VMHandle a_sourceHandle, VMHandle a_destHandle) = 0;																																																					  // 20
		virtual void ResetAllBoundObjects(VMHandle a_objHandle) = 0;																																																										  // 21
		virtual bool CastObject(const BSTSmartPointer<Object>& a_sourceObj, const BSTSmartPointer<ObjectTypeInfo>& a_targetType, BSTSmartPointer<Object>& a_castedObj) = 0;																																	  // 22
		virtual bool SetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const Variable& a_newValue, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;																												  // 23
		virtual bool GetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propName, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;																																			  // 24
		virtual bool GetVariableValue(VMHandle a_objHandle, const BSFixedString& a_scriptName, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																						  // 26
		virtual bool GetVariableValue(const BSTSmartPointer<Object>& a_obj, std::uint32_t a_varIndex, Variable& a_var) const = 0;																																											  // 25
		virtual bool HandleImplementsEvent(VMHandle a_object, const BSFixedString& a_eventName) const = 0;																																																	  // 27
		virtual bool AddEventRelay(VMHandle a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;																																								  // 28
		virtual void RemoveEventRelay(VMHandle a_sourceObject, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_destObj) = 0;																																								  // 29
		virtual void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_destObj) = 0;																																																					  // 2A
		virtual void SendEvent(VMHandle a_objHandle, const BSFixedString& a_eventName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filter, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0; // 2B
		virtual bool DispatchStaticCall(const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;															  // 2C
		virtual bool DispatchMethodCall(VMHandle a_objHandle, const BSFixedString& a_objName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;										  // 2E
		virtual bool DispatchMethodCall(const BSTSmartPointer<Object>& a_self, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;													  // 2D
		virtual bool DispatchUnboundMethodCall(VMHandle a_objHandle, const BSTSmartPointer<BoundScript>& a_script, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_arguments, const BSTSmartPointer<IStackCallbackFunctor>& a_callback) = 0;				  // 2F
		virtual bool IsWaitingOnLatent(VMStackID a_stackID) const = 0;																																																										  // 30
		virtual void ReturnFromLatent(VMStackID a_stackID, const Variable& a_retValue) = 0;																																																					  // 31
		[[nodiscard]] virtual ErrorLogger& GetErrorLogger() const = 0;																																																										  // 32
		[[nodiscard]] virtual const IObjectHandlePolicy& GetObjectHandlePolicy() const = 0;																																																					  // 34
		[[nodiscard]] virtual IObjectHandlePolicy& GetObjectHandlePolicy() = 0;																																																								  // 33
		[[nodiscard]] virtual const ObjectBindPolicy& GetObjectBindPolicy() const = 0;																																																						  // 36
		[[nodiscard]] virtual ObjectBindPolicy& GetObjectBindPolicy() = 0;																																																									  // 35
		[[nodiscard]] virtual ISavePatcherInterface& GetSavePatcherInterface() = 0;																																																							  // 37
		virtual void RegisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;																																																								  // 38
		virtual void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_sink) = 0;																																																								  // 39
		virtual void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;																																																							  // 3A
		virtual void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_sink) = 0;																																																							  // 3B
		virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, ErrorLogger::Severity a_severity) const = 0;																																										  // 3D
		virtual void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, VMStackID a_stackID, ErrorLogger::Severity a_severity) const = 0;																																					  // 3C

		template <class F>
		void BindNativeMethod(
			stl::zstring a_object,
			stl::zstring a_function,
			F a_func,
			std::optional<bool> a_taskletCallable = std::nullopt,
			bool a_isLatent = false);

		template <class... Args>
		bool DispatchStaticCall(
			const BSFixedString& a_objName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callback,
			Args&&... a_args);

		template <class... Args>
		bool DispatchMethodCall(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callback,
			Args&&... a_args);

		template <class T>
			requires std::is_same_v<typename std::remove_cv_t<T>::value_type, Variable>
		bool DispatchAppliedStaticCall(
			const BSFixedString& a_objName,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callback,
			const T& a_args);

		template <class T>
			requires std::is_same_v<typename std::remove_cv_t<T>::value_type, Variable>
		bool DispatchAppliedMethodCall(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callback,
			const T& a_args);

		void PostError(std::string_view a_msg, VMStackID a_stackID, ErrorLogger::Severity a_severity)
		{
			class ErrorImpl
				: public ICachedErrorMessage
			{
			public:
				ErrorImpl(std::string_view a_message) noexcept :
					_message(a_message)
				{
				}

				void GetErrorMsg(BSFixedString& a_message) const override { a_message = _message; }

			private:
				std::string_view _message;
			};

			const ErrorImpl e{ a_msg };
			PostCachedErrorToLogger(e, a_stackID, a_severity);
		}
	};
	static_assert(sizeof(IVirtualMachine) == 0x10);
}
