#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_IVMDebugInterface.hpp"
#include "RE/B/BSScript_IVMObjectBindInterface.hpp"
#include "RE/B/BSScript_IVMSaveLoadInterface.hpp"
#include "RE/B/BSScript_IVirtualMachine.hpp"
#include "RE/B/BSScript_Internal_AttachedScript.hpp"
#include "RE/B/BSScript_Internal_EventRelay.hpp"
#include "RE/B/BSScript_Internal_FunctionMessage.hpp"
#include "RE/B/BSScript_Internal_ReadableStringTable.hpp"
#include "RE/B/BSScript_Internal_ReadableTypeTable.hpp"
#include "RE/B/BSScript_Internal_WritableStringTable.hpp"
#include "RE/B/BSScript_Internal_WritableTypeTable.hpp"
#include "RE/B/BSScript_LinkerProcessor.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTFreeList.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTMessageQueue.hpp"
#include "RE/B/BSTObjectArena.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTThreadScrapFunction.hpp"
#include "RE/M/MemoryManager.hpp"
#include "msvc/memory.hpp"

namespace RE::BSScript
{
	enum class FreezeState : std::int32_t;

	class Array;
	class ErrorLogger;
	class IClientVM;
	class IMemoryPagePolicy;
	class IObjectHandlePolicy;
	class IProfilePolicy;
	class ISavePatcherInterface;
	class IStackCallbackSaveInterface;
	class Object;
	class ObjectBindPolicy;
	class ObjectTypeInfo;
	class Stack;
	class StatsEvent;
	class Struct;
	class StructTypeInfo;
}

namespace RE::BSScript::Internal
{
	class CodeTasklet;
	class SuspendedStack;

	class __declspec(novtable) VirtualMachine :
		public IVirtualMachine,			  // 0x0000
		public IVMObjectBindInterface,	  // 0x0010
		public IVMSaveLoadInterface,	  // 0x0018
		public IVMDebugInterface,		  // 0x0020
		public BSTEventSource<StatsEvent> // 0x0028
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSScript__Internal__VirtualMachine;
		inline static constexpr const auto& VTABLE = VTABLE::BSScript__Internal__VirtualMachine;

		inline static constexpr auto EMPTY_STACK_ID = static_cast<StackID>(0);
		inline static constexpr auto EMPTY_SAVE_HANDLE = static_cast<SaveHandle>(0);

		class LoadedArrayEntry
		{
		public:
			// members
			BSTSmartPointer<Array> array; // 0x00
			std::uint32_t arraySize;	  // 0x08
		};

		static_assert(sizeof(LoadedArrayEntry) == 0x10);

		class PendingLatentReturn
		{
		public:
			GAME_HEAP_REDEFINE_NEW(PendingLatentReturn);

			// members
			StackID stackID;	  // 0x00
			Variable returnValue; // 0x08
		};

		static_assert(sizeof(PendingLatentReturn) == 0x18);

		class QueuedUnbindRefs
		{
		public:
			// members
			BSTSmartPointer<Object> object; // 0x00
			std::uint32_t refCount;			// 0x08
		};

		static_assert(sizeof(QueuedUnbindRefs) == 0x10);

		~VirtualMachine() override; // 0x00

		// override (IVirtualMachine)
		void SetLoader(ILoader* a_newLoader) override;										   // 0x01
		void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) override;			   // 0x02
		void Update(REX::Float32 a_updateBudget) override;									   // 0x03
		void UpdateTasklets(REX::Float32 a_updateBudget) override;							   // 0x04
		void SetOverstressed(bool a_overstressed) override;									   // 0x05
		auto IsCompletelyFrozen() const -> bool override;									   // 0x06
		auto RegisterObjectType(FormType a_typeID, const char* a_scriptName) -> bool override; // 0x07
		auto GetScriptObjectType(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo)
			-> bool override; // 0x09
		auto GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo)
			-> bool override; // 0x08
		auto GetScriptObjectTypeNoLoad(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo) const
			-> bool override; // 0x0B
		auto GetScriptObjectTypeNoLoad(
			const BSFixedString& a_scriptName,
			BSTSmartPointer<ObjectTypeInfo>& a_outObjectTypeInfo) const -> bool override; // 0x0A
		auto GetTypeIDForScriptObject(const BSFixedString& a_scriptName, FormType& a_typeID) const
			-> bool override;																			   // 0x0C
		void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_outObjectTypeList) const override; // 0x0D
		auto GetParentNativeType(
			const BSFixedString& a_childTypeName,
			BSTSmartPointer<ObjectTypeInfo>& a_outParentTypeInfo) -> bool override; // 0x0E
		auto TypeIsValid(const BSFixedString& a_scriptName) -> bool override;		// 0x0F
		auto ReloadType(const char* a_scriptName) -> bool override;					// 0x10
		void TasksToJobs(JobList& a_jobList) override;								// 0x11
		void CalculateFullReloadList(
			const BSTSet<BSFixedString>& a_scriptSet,
			BSTScrapObjectArena<BSFixedString, 0x20>& a_outScriptList) const override; // 0x12
		auto GetScriptStructType(
			const BSFixedString& a_structTypeName,
			BSTSmartPointer<StructTypeInfo>& a_outStructType) -> bool override; // 0x13
		auto GetScriptStructTypeNoLoad(
			const BSFixedString& a_structTypeName,
			BSTSmartPointer<StructTypeInfo>& a_outStructType) const -> bool override; // 0x14
		auto GetChildStructTypes(
			const BSFixedString& a_parentObjectName,
			BSTScrapObjectArena<BSFixedString, 0x20>& a_outStructTypes) const -> bool override; // 0x15
		auto CreateObject(
			const BSFixedString& a_scriptName,
			const BSTScrapHashMap<BSFixedString, Variable>& a_properties,
			BSTSmartPointer<Object>& a_outNewObject) -> bool override; // 0x16
		auto CreateObject(const BSFixedString& a_scriptName, BSTSmartPointer<Object>& a_outNewObject)
			-> bool override; // 0x17
		auto CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_outNewStruct)
			-> bool override; // 0x18
		auto CreateArray(
			TypeInfo::RawType a_elementType,
			const BSFixedString& a_elementObjectTypeName,
			std::uint32_t a_elementCount,
			BSTSmartPointer<Array>& a_outNewArray) -> bool override; // 0x1A
		auto CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_outNewArray)
			-> bool override;									   // 0x19
		auto BindNativeMethod(IFunction* a_func) -> bool override; // 0x1B
		void SetCallableFromTasklets(const char* a_scriptName, const char* a_funcName, bool a_taskletCallable)
			override; // 0x1D
		void SetCallableFromTasklets(
			const char* a_scriptName,
			const char* a_stateName,
			const char* a_funcName,
			bool a_taskletCallable) override; // 0x1C
		void ForEachBoundObject(
			ObjectHandle a_objectHandle,
			const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) override; // 0x1E
		auto FindBoundObject(
			ObjectHandle a_objectHandle,
			const char* a_scriptName,
			bool a_allowConst,
			BSTSmartPointer<Object>& a_outAttachedObject,
			bool a_exactType) const -> bool override;														  // 0x1F
		void MoveBoundObjects(ObjectHandle a_sourceObjectHandle, ObjectHandle a_targetObjectHandle) override; // 0x20
		void ResetAllBoundObjects(ObjectHandle a_objectHandle) override;									  // 0x21
		auto CastObject(
			const BSTSmartPointer<Object>& a_sourceObject,
			const BSTSmartPointer<ObjectTypeInfo>& a_targetType,
			BSTSmartPointer<Object>& a_castedObject) -> bool override; // 0x22
		auto SetPropertyValue(
			const BSTSmartPointer<Object>& a_self,
			const char* a_propertyName,
			const Variable& a_newValue,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool override; // 0x23
		auto GetPropertyValue(
			const BSTSmartPointer<Object>& a_self,
			const char* a_propertyName,
			const BSTSmartPointer<IStackCallbackFunctor>& a_outCallbackFunctor) -> bool override; // 0x24
		auto GetVariableValue(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_scriptName,
			std::uint32_t a_varIndex,
			Variable& a_outVar) const -> bool override; // 0x26
		auto GetVariableValue(const BSTSmartPointer<Object>& a_object, std::uint32_t a_varIndex, Variable& a_outVar)
			const -> bool override; // 0x25
		auto HandleImplementsEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName) const
			-> bool override; // 0x27
		auto AddEventRelay(
			ObjectHandle a_sourceObjectHandle,
			const BSFixedString& a_eventName,
			const BSTSmartPointer<Object>& a_targetObject) -> bool override; // 0x28
		void RemoveEventRelay(
			ObjectHandle a_sourceObjectHandle,
			const BSFixedString& a_eventName,
			const BSTSmartPointer<Object>& a_targetObject) override;					   // 0x29
		void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_targetObject) override; // 0x2A
		void SendEvent(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_eventName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filterFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override; // 0x2B
		auto DispatchStaticCall(
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool override; // 0x2C
		auto DispatchMethodCall(
			ObjectHandle a_objectHandle,
			const BSFixedString& a_scriptName,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool override; // 0x2E
		auto DispatchMethodCall(
			const BSTSmartPointer<Object>& a_self,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool override; // 0x2D
		auto DispatchUnboundMethodCall(
			ObjectHandle a_objectHandle,
			const BSTSmartPointer<BoundScript>& a_script,
			const BSFixedString& a_funcName,
			const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor,
			const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) -> bool override; // 0x2F
		auto IsWaitingOnLatent(StackID a_stackID) const -> bool override;					   // 0x30
		void ReturnFromLatent(StackID a_stackID, const Variable& a_result) override;		   // 0x31
		auto GetErrorLogger() const -> ErrorLogger& override;								   // 0x32
		auto GetObjectHandlePolicy() const -> const IObjectHandlePolicy& override;			   // 0x34
		auto GetObjectHandlePolicy() -> IObjectHandlePolicy& override;						   // 0x33
		auto GetObjectBindPolicy() const -> const ObjectBindPolicy& override;				   // 0x36
		auto GetObjectBindPolicy() -> ObjectBindPolicy& override;							   // 0x35
		auto GetSavePatcherInterface() -> ISavePatcherInterface& override;					   // 0x37
		void RegisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) override;				   // 0x38
		void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) override;			   // 0x39
		void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) override;			   // 0x3A
		void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) override;		   // 0x3B
		void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, LogSeverity a_severity)
			const override; // 0x3D
		void PostCachedErrorToLogger(
			const ICachedErrorMessage& a_errorFunctor,
			StackID a_stackID,
			LogSeverity a_severity) const override; // 0x3C

		// override (IVMObjectBindInterface)
		auto GetBoundHandle(const BSTSmartPointer<Object>& a_object) const -> ObjectHandle override;  // 0x01
		void TypeCanBeBound(const BSFixedString& a_scriptName, ObjectHandle a_objectHandle) override; // 0x02
		void BindObject(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional)
			override; // 0x03
		void HandleLoadedBinding(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional)
			override;																// 0x04
		void RemoveAllBoundObjects(ObjectHandle a_objectHandle) override;			// 0x05
		void RemoveAllDiskLoadedBoundObjects(ObjectHandle a_objectHandle) override; // 0x06
		void HandleCObjectDeletion(ObjectHandle a_objectHandle) override;			// 0x07
		void UnbindObject(const BSTSmartPointer<Object>& a_object) override;		// 0x08
		auto CreateObject(
			const BSFixedString& a_scriptName,
			std::uint32_t a_numProperties,
			BSTSmartPointer<Object>& a_outObject) -> bool override; // 0x09
		auto InitObjectProperties(
			const BSTSmartPointer<Object>& a_object,
			const BSTScrapHashMap<BSFixedString, Variable>& a_properties,
			std::uint32_t a_unk01,
			bool a_unk02) -> bool override; // 0x0A

		// override (IVMSaveLoadInterface)
		auto SaveGame(BSStorage& a_storage, const IHandleReaderWriter& a_handleReaderWriter, bool a_calculatingSize)
			-> bool override; // 0x01
		auto LoadGame(
			const BSStorage& a_storage,
			const IHandleReaderWriter& a_handleReaderWriter,
			bool& a_unk01,
			bool& a_unk02) -> bool override;												   // 0x02
		void MarkSaveInvalid(BSStorage& a_storage) override;								   // 0x03
		auto GetSaveGameVersion() const -> std::uint16_t override;							   // 0x04
		void CleanupSave() override;														   // 0x05
		void CleanupLoad() override;														   // 0x06
		void DropAllRunningData() override;													   // 0x07
		auto GetSaveHandleForObject(const Object* a_object) const -> SaveHandle override;	   // 0x08
		void SetSaveHandleForObject(const Object* a_object, SaveHandle a_saveHandle) override; // 0x09
		auto GetObjectBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Object>& a_object) const
			-> bool override; // 0x0A
		auto GetObjectBySaveHandle(
			SaveHandle a_saveHandle,
			const TypeInfo& a_typeInfo,
			BSTSmartPointer<Object>& a_object) const -> bool override;						   // 0x0B
		auto GetSaveHandleForStruct(const Struct* a_struct) const -> SaveHandle override;	   // 0x0C
		void SetSaveHandleForStruct(const Struct* a_struct, SaveHandle a_saveHandle) override; // 0x0D
		auto GetStructBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Struct>& a_struct) const
			-> bool override;																// 0x0E
		auto GetSaveHandleForArray(const Array* a_array) const -> SaveHandle override;		// 0x0F
		void SetSaveHandleForArray(const Array* a_array, SaveHandle a_saveHandle) override; // 0x10
		auto GetArrayBySaveHandle(SaveHandle a_saveHandle, BSTSmartPointer<Array>& a_array) const
			-> bool override;																			   // 0x11
		auto GetStackByID(StackID a_stackID, BSTSmartPointer<Stack>& a_stack) const -> bool override;	   // 0x12
		auto GetWritableStringTable() -> Internal::WritableStringTable& override;						   // 0x13
		auto GetWritableStringTable() const -> const Internal::WritableStringTable& override;			   // 0x14
		auto GetReadableStringTable() const -> Internal::ReadableStringTable& override;					   // 0x15
		auto GetWritableTypeTable() -> Internal::WritableTypeTable& override;							   // 0x16
		auto GetWritableTypeTable() const -> const Internal::WritableTypeTable& override;				   // 0x17
		auto GetReadableTypeTable() const -> Internal::ReadableTypeTable& override;						   // 0x18
		auto CreateEmptyTasklet(Stack* a_stack, BSTSmartPointer<CodeTasklet>& a_tasklet) -> bool override; // 0x19

		// override (IVMDebugInterface)
		void DumpRunningStacksToLog() override;														 // 0x01
		void DumpStackFrameToLog(StackID a_stackID, std::uint32_t a_frame, bool a_verbose) override; // 0x02
		void GetStackFrame(StackID a_stackID, std::uint32_t a_frame, bool a_wantFilename, BSFixedString& a_stackFrame)
			override;																							 // 0x03
		void DumpPersistenceInformationToLog(const char* a_logfile, ObjectHandle a_objectHandle) const override; // 0x04
		void DumpEventRelayInformationToLog(
			const char* a_logfile,
			ObjectHandle a_objectHandle,
			const BSFixedString& a_propertyName) const override; // 0x05

		GAME_HEAP_REDEFINE_NEW(VirtualMachine);

		[[nodiscard]]
		auto IsStackRunning(StackID a_stackId) const noexcept -> bool;

		auto AttemptFunctionCall(
			Stack& a_stack,
			const BSTSmartPointer<IFuncCallQuery>& a_funcCallQuery,
			bool a_inScriptTasklet) -> bool;

		// members
		ErrorLogger* errorLogger;													   // 0x0080
		IMemoryPagePolicy* memoryPagePolicy;										   // 0x0088
		IObjectHandlePolicy* handlePolicy;											   // 0x0090
		ObjectBindPolicy* objectBindPolicy;											   // 0x0098
		IClientVM* clientVM;														   // 0x00A0
		IStackCallbackSaveInterface* stackCallbackSaveInterface;					   // 0x00A8
		IProfilePolicy* profilePolicy;												   // 0x00B0
		ISavePatcherInterface* savePatcherInterface;								   // 0x00B8
		mutable BSSpinLock typeInfoLock;											   // 0x00C0
		LinkerProcessor linker;														   // 0x00C8
		BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>> objectTypeMap;	   // 0x0168
		BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>> structTypeMap;	   // 0x0198
		BSTHashMap<FormType, BSFixedString> typeIDToObjectType;						   // 0x01C8
		BSTHashMap<BSFixedString, FormType> objectTypeToTypeID;						   // 0x01F8
		BSTArray<BSTSmartPointer<ObjectTypeInfo>> typesToUnload;					   // 0x0228
		mutable BSSpinLock funcQueueLock;											   // 0x0240
		BSTStaticFreeList<FunctionMessage, 0x400> funcMsgPool;						   // 0x0248
		BSTCommonLLMessageQueue<FunctionMessage> funcMsgQueue;						   // 0x8260
		BSTArray<FunctionMessage> overflowFuncMsgs;									   // 0x8288
		BSTArray<CodeTasklet*> vmTasks;												   // 0x82A0
		std::uint32_t waitingFuncMsgs;												   // 0x82B8
		bool overstressed;															   // 0x82BC
		bool initialized;															   // 0x82BD
		std::array<std::byte, 0xBD00 - 0x82BE> pad82BE;								   // 0x82BE
		BSTArray<SuspendedStack> overflowSuspendArray01;							   // 0xBD00
		BSTArray<SuspendedStack> overflowSuspendArray02;							   // 0xBD18
		mutable BSSpinLock suspendQueueLock;										   // 0xBD30
		std::array<std::byte, 0xBD40 - 0xBD38> padBD38;								   // 0xBD38
		BSTArray<SuspendedStack>* stacksToResumeOverflow;							   // 0xBD40
		std::array<std::byte, 0xBD50 - 0xBD48> padBD48;								   // 0xBD48
		BSTArray<SuspendedStack>* stacksToSuspendOverflow;							   // 0xBD50
		mutable BSSpinLock runningStacksLock;										   // 0xBD58
		BSTHashMap<StackID, BSTSmartPointer<Stack>> allRunningStacks;				   // 0xBD60
		BSTHashMap<StackID, BSTSmartPointer<Stack>> waitingLatentReturns;			   // 0xBD90
		StackID nextStackID;														   // 0xBDC0
		mutable BSSpinLock frozenStacksLock;										   // 0xBDC4
		std::array<std::byte, 0xBDD0 - 0xBDCC> padBDCC;								   // 0xBDCC
		BSTArray<msvc::unique_ptr<PendingLatentReturn>> pendingLatentReturns;		   // 0xBDD0
		BSTSmartPointer<BSScript::Stack> frozenStacksHead;							   // 0xBDE8
		std::uint32_t frozenStacksCount;											   // 0xBDF0
		REX::Enum<FreezeState, std::int32_t> freezeState;							   // 0xBDF4
		mutable BSSpinLock attachedScriptsLock;										   // 0xBDF8
		BSTHashMap<ObjectHandle, BSTSmallSharedArray<AttachedScript>> attachedScripts; // 0xBE00
		std::uint32_t nextObjectToClean;											   // 0xBE30
		std::array<std::byte, 0xBE38 - 0xBE34> padBE34;								   // 0xBE34
		ObjectHandle nextAttachedObjectToClean;										   // 0xBE38
		BSTArray<BSTSmartPointer<Object>> detachedScripts;							   // 0xBE40
		mutable BSSpinLock structsLock;												   // 0xBE58
		std::uint32_t nextStructToClean;											   // 0xBE60
		std::array<std::byte, 0xBE68 - 0xBE64> padBE64;								   // 0xBE64
		BSTArray<BSTSmartPointer<Struct>> allStructs;								   // 0xBE68
		mutable BSSpinLock arraysLock;												   // 0xBE80
		std::uint32_t nextArrayToClean;												   // 0xBE88
		std::array<std::byte, 0xBE90 - 0xBE8C> padBE8C;								   // 0xBE8C
		BSTArray<BSTSmartPointer<Array>> arrays;									   // 0xBE90
		mutable BSSpinLock objectResetLock;											   // 0xBEA8
		BSTArray<BSTSmartPointer<Object>> objectsAwaitingReset;						   // 0xBEB0
		mutable BSSpinLock loadTableLock;											   // 0xBEC8
		BSTHashMap<ObjectHandle, BSTSmartPointer<Object>> loadTable;				   // 0xBED0
		BSTHashMap<ObjectHandle, ObjectHandle> loadHandlesTable;					   // 0xBF00
		BSTHashMap<ObjectHandle, BSTSmartPointer<Struct>> structLoadTable;			   // 0xBF30
		BSTHashMap<ObjectHandle, LoadedArrayEntry> arrayLoadTable;					   // 0xBF60
		mutable BSSpinLock queuedUnbindLock;										   // 0xBF90
		BSTArray<QueuedUnbindRefs> queuedUnbinds;									   // 0xBF98
		mutable BSSpinLock eventRelayLock;											   // 0xBFB0
		BSTHashMap<ObjectHandle, BSTSmartPointer<EventRelay>> eventRelays;			   // 0xBFB8
		std::uint16_t currentSaveGameVersion;										   // 0xBFE8
		std::array<std::byte, 0xBFEC - 0xBFEA> padBFEA;								   // 0xBFEA
		std::uint32_t saveObjectCount;												   // 0xBFEC
		std::uint32_t saveStructCount;												   // 0xBFF0
		std::uint32_t saveArrayCount;												   // 0xBFF4
		WritableStringTable writableStringTable;									   // 0xBFF8
		ReadableStringTable readableStringTable;									   // 0xC010
		WritableTypeTable writableTypeTable;										   // 0xC028
		ReadableTypeTable readableTypeTable;										   // 0xC038
		std::array<std::byte, 0xC080 - 0xC040> padC040;								   // 0xC040
	};

	static_assert(sizeof(VirtualMachine) == 0xC080);
}
