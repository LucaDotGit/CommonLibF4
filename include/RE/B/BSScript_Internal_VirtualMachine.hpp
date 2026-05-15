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
	class IStackCallbackFunctor;
	class IStackCallbackSaveInterface;
	class ObjectBindPolicy;
	class Stack;
	class StatsEvent;
}

namespace RE::BSScript::Internal
{
	class CodeTasklet;
	class SuspendedStack;

	class __declspec(novtable) VirtualMachine
		: public IVirtualMachine,			// 0000
		  public IVMObjectBindInterface,	// 0010
		  public IVMSaveLoadInterface,		// 0018
		  public IVMDebugInterface,			// 0020
		  public BSTEventSource<StatsEvent> // 0028
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSScript__Internal__VirtualMachine };
		inline static constexpr auto VTABLE{ VTABLE::BSScript__Internal__VirtualMachine };

		inline static constexpr auto EMPTY_STACK_ID = static_cast<StackID>(0);
		inline static constexpr auto EMPTY_SAVE_HANDLE = static_cast<ObjectHandle>(0);

		class LoadedArrayEntry
		{
		public:
			// members
			BSTSmartPointer<Array> array; // 00
			std::uint32_t arraySize;	  // 08
		};
		static_assert(sizeof(LoadedArrayEntry) == 0x10);

		class PendingLatentReturn
		{
		public:
			GAME_HEAP_REDEFINE_NEW(PendingLatentReturn);

			// members
			StackID stackID;	  // 00
			Variable returnValue; // 08
		};
		static_assert(sizeof(PendingLatentReturn) == 0x18);

		class QueuedUnbindRefs
		{
		public:
			// members
			BSTSmartPointer<Object> object; // 00
			std::uint32_t refCount;			// 08
		};
		static_assert(sizeof(QueuedUnbindRefs) == 0x10);

		~VirtualMachine() override; // 00

		// override (IVirtualMachine)
		void SetLoader(ILoader* a_newLoader) override;																																																																			  // 01
		void SetLinkedCallback(ITypeLinkedCallback* a_typeLinkedCallback) override;																																																												  // 02
		void Update(REX::Float32 a_updateBudget) override;																																																																		  // 03
		void UpdateTasklets(REX::Float32 a_updateBudget) override;																																																																  // 04
		void SetOverstressed(bool a_overstressed) override;																																																																		  // 05
		bool IsCompletelyFrozen() const override;																																																																				  // 06
		bool RegisterObjectType(FormType a_typeID, const char* a_scriptName) override;																																																											  // 07
		bool GetScriptObjectType(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) override;																																																				  // 09
		bool GetScriptObjectType(const BSFixedString& a_name, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) override;																																																		  // 08
		bool GetScriptObjectTypeNoLoad(FormType a_typeID, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) const override;																																																	  // 0B
		bool GetScriptObjectTypeNoLoad(const BSFixedString& a_scriptName, BSTSmartPointer<ObjectTypeInfo>& a_objectTypeInfo) const override;																																													  // 0A
		bool GetTypeIDForScriptObject(const BSFixedString& a_scriptName, FormType& a_typeID) const override;																																																					  // 0C
		void GetScriptObjectsWithATypeID(BSScrapArray<BSFixedString>& a_objectTypeList) const override;																																																							  // 0D
		bool GetParentNativeType(const BSFixedString& a_childTypeName, BSTSmartPointer<ObjectTypeInfo>& a_parentTypeInfo) override;																																																  // 0E
		bool TypeIsValid(const BSFixedString& a_scriptName) override;																																																															  // 0F
		bool ReloadType(const char* a_scriptName) override;																																																																		  // 10
		void TasksToJobs(JobList& a_jobList) override;																																																																			  // 11
		void CalculateFullReloadList(const BSTSet<BSFixedString>& a_scriptSet, BSTScrapObjectArena<BSFixedString, 32>& a_scriptList) const override;																																											  // 12
		bool GetScriptStructType(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) override;																																																  // 13
		bool GetScriptStructTypeNoLoad(const BSFixedString& a_structTypeName, BSTSmartPointer<StructTypeInfo>& a_structType) const override;																																													  // 14
		bool GetChildStructTypes(const BSFixedString& a_parentObjectName, BSTScrapObjectArena<BSFixedString, 32>& a_structTypes) const override;																																												  // 15
		bool CreateObject(const BSFixedString& a_scriptName, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, BSTSmartPointer<Object>& a_newObject) override;																																						  // 16
		bool CreateObject(const BSFixedString& a_scriptName, BSTSmartPointer<Object>& a_newObject) override;																																																					  // 17
		bool CreateStruct(const BSFixedString& a_structTypeName, BSTSmartPointer<Struct>& a_newStruct) override;																																																				  // 18
		bool CreateArray(TypeInfo::RawType a_elementType, const BSFixedString& a_elementObjectTypeName, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) override;																																				  // 1A
		bool CreateArray(const TypeInfo& a_type, std::uint32_t a_elementCount, BSTSmartPointer<Array>& a_newArray) override;																																																	  // 19
		bool BindNativeMethod(IFunction* a_func) override;																																																																		  // 1B
		void SetCallableFromTasklets(const char* a_scriptName, const char* a_funcName, bool a_taskletCallable) override;																																																		  // 1D
		void SetCallableFromTasklets(const char* a_scriptName, const char* a_stateName, const char* a_funcName, bool a_taskletCallable) override;																																												  // 1C
		void ForEachBoundObject(ObjectHandle a_objectHandle, const BSTThreadScrapFunction<BSContainer::ForEachResult(Object*)>& a_functor) override;																																											  // 1E
		bool FindBoundObject(ObjectHandle a_objectHandle, const char* a_scriptName, bool a_allowConst, BSTSmartPointer<Object>& a_attachedObject, bool a_exactType) const override;																																				  // 1F
		void MoveBoundObjects(ObjectHandle a_sourceObjectHandle, ObjectHandle a_targetObjectHandle) override;																																																					  // 20
		void ResetAllBoundObjects(ObjectHandle a_objectHandle) override;																																																														  // 21
		bool CastObject(const BSTSmartPointer<Object>& a_sourceObject, const BSTSmartPointer<ObjectTypeInfo>& a_targetType, BSTSmartPointer<Object>& a_castedObject) override;																																					  // 22
		bool SetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propertyName, const Variable& a_newValue, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;																															  // 23
		bool GetPropertyValue(const BSTSmartPointer<Object>& a_self, const char* a_propertyName, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;																																						  // 24
		bool GetVariableValue(ObjectHandle a_objectHandle, const BSFixedString& a_scriptName, std::uint32_t a_varIndex, Variable& a_var) const override;																																										  // 26
		bool GetVariableValue(const BSTSmartPointer<Object>& a_object, std::uint32_t a_varIndex, Variable& a_var) const override;																																																  // 25
		bool HandleImplementsEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName) const override;																																																				  // 27
		bool AddEventRelay(ObjectHandle a_sourceObjectHandle, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_targetObject) override;																																										  // 28
		void RemoveEventRelay(ObjectHandle a_sourceObjectHandle, const BSFixedString& a_eventName, const BSTSmartPointer<Object>& a_targetObject) override;																																										  // 29
		void RemoveAllEventRelays(const BSTSmartPointer<Object>& a_targetObject) override;																																																										  // 2A
		void SendEvent(ObjectHandle a_objectHandle, const BSFixedString& a_eventName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTThreadScrapFunction<bool(const BSTSmartPointer<Object>&)>& a_filterFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override; // 2B
		bool DispatchStaticCall(const BSFixedString& a_scriptName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;																		  // 2C
		bool DispatchMethodCall(ObjectHandle a_objectHandle, const BSFixedString& a_scriptName, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;											  // 2E
		bool DispatchMethodCall(const BSTSmartPointer<Object>& a_self, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;																	  // 2D
		bool DispatchUnboundMethodCall(ObjectHandle a_objectHandle, const BSTSmartPointer<BoundScript>& a_script, const BSFixedString& a_funcName, const BSTThreadScrapFunction<bool(BSScrapArray<Variable>&)>& a_argsFunctor, const BSTSmartPointer<IStackCallbackFunctor>& a_callbackFunctor) override;						  // 2F
		bool IsWaitingOnLatent(StackID a_stackID) const override;																																																																  // 30
		void ReturnFromLatent(StackID a_stackID, const Variable& a_result) override;																																																											  // 31
		ErrorLogger& GetErrorLogger() const override;																																																																			  // 32
		const IObjectHandlePolicy& GetObjectHandlePolicy() const override;																																																														  // 34
		IObjectHandlePolicy& GetObjectHandlePolicy() override;																																																																	  // 33
		const ObjectBindPolicy& GetObjectBindPolicy() const override;																																																															  // 36
		ObjectBindPolicy& GetObjectBindPolicy() override;																																																																		  // 35
		ISavePatcherInterface& GetSavePatcherInterface() override;																																																																  // 37
		void RegisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) override;																																																													  // 38
		void UnregisterForLogEvent(BSTEventSink<LogEvent>* a_eventSink) override;																																																												  // 39
		void RegisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) override;																																																												  // 3A
		void UnregisterForStatsEvent(BSTEventSink<StatsEvent>* a_eventSink) override;																																																											  // 3B
		void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, ErrorLogger::Severity a_severity = ErrorLogger::Severity::kError) const override;																																								  // 3D
		void PostCachedErrorToLogger(const ICachedErrorMessage& a_errorFunctor, StackID a_stackID, ErrorLogger::Severity a_severity = ErrorLogger::Severity::kError) const override;																																			  // 3C

		// override (IVMObjectBindInterface)
		ObjectHandle GetBoundHandle(const BSTSmartPointer<Object>& a_object) const override;															   // 01
		void TypeCanBeBound(const BSFixedString& a_scriptName, ObjectHandle a_objectHandle) override;													   // 02
		void BindObject(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional) override;									   // 03
		void HandleLoadedBinding(BSTSmartPointer<Object>& a_object, ObjectHandle a_objectHandle, bool a_conditional) override;							   // 04
		void RemoveAllBoundObjects(ObjectHandle a_objectHandle) override;																				   // 05
		void RemoveAllDiskLoadedBoundObjects(ObjectHandle a_objectHandle) override;																		   // 06
		void HandleCObjectDeletion(ObjectHandle a_objectHandle) override;																				   // 07
		void UnbindObject(const BSTSmartPointer<Object>& a_object) override;																			   // 08
		bool CreateObjectWithProperties(const BSFixedString& a_scriptName, std::uint32_t a_numProperties, BSTSmartPointer<Object>& a_object) override;	   // 09
		bool InitObjectProperties(BSTSmartPointer<Object>& a_object, const BSTScrapHashMap<BSFixedString, Variable>& a_properties, bool a_unk01) override; // 0A

		// override (IVMSaveLoadInterface)
		bool SaveGame(BSStorage& a_storage, const IHandleReaderWriter& a_handleReaderWriter, bool a_calculatingSize) override;				   // 01
		bool LoadGame(const BSStorage& a_storage, const IHandleReaderWriter& a_handleReaderWriter, bool& a_unk01, bool& a_unk02) override;	   // 02
		void MarkSaveInvalid(BSStorage& a_storage) override;																				   // 03
		std::uint16_t GetSaveGameVersion() const override;																					   // 04
		void CleanupSave() override;																										   // 05
		void CleanupLoad() override;																										   // 06
		void DropAllRunningData() override;																									   // 07
		ObjectHandle GetSaveHandleForObject(const Object* a_object) const override;															   // 08
		void SetSaveHandleForObject(const Object* a_object, ObjectHandle a_objectHandle) override;											   // 09
		bool GetObjectBySaveHandle(ObjectHandle a_objectHandle, BSTSmartPointer<Object>& a_object) const override;							   // 0A
		bool GetObjectBySaveHandle(ObjectHandle a_objectHandle, const TypeInfo& a_typeInfo, BSTSmartPointer<Object>& a_object) const override; // 0B
		ObjectHandle GetSaveHandleForStruct(const Struct* a_struct) const override;															   // 0C
		void SetSaveHandleForStruct(const Struct* a_struct, ObjectHandle a_objectHandle) override;											   // 0D
		bool GetStructBySaveHandle(ObjectHandle a_Handle, BSTSmartPointer<Struct>& a_struct) const override;								   // 0E
		ObjectHandle GetSaveHandleForArray(const Array* a_array) const override;															   // 0F
		void SetSaveHandleForArray(const Array* a_array, ObjectHandle a_objectHandle) override;												   // 10
		bool GetArrayBySaveHandle(ObjectHandle a_objectHandle, BSTSmartPointer<Array>& a_array) const override;								   // 11
		bool GetStackByID(StackID a_stackID, BSTSmartPointer<Stack>& a_stack) const override;												   // 12
		Internal::WritableStringTable& GetWritableStringTable() override;																	   // 13
		const Internal::WritableStringTable& GetWritableStringTable() const override;														   // 14
		Internal::ReadableStringTable& GetReadableStringTable() const override;																   // 15
		Internal::WritableTypeTable& GetWritableTypeTable() override;																		   // 16
		const Internal::WritableTypeTable& GetWritableTypeTable() const override;															   // 17
		Internal::ReadableTypeTable& GetReadableTypeTable() const override;																	   // 18
		bool CreateEmptyTasklet(Stack* a_stack, BSTSmartPointer<CodeTasklet>& a_tasklet) override;											   // 19

		// override (IVMDebugInterface)
		void DumpRunningStacksToLog() override;																										 // 01
		void DumpStackFrameToLog(StackID a_stackID, std::uint32_t a_frame, bool a_verbose) override;												 // 02
		void GetStackFrame(StackID a_stackID, std::uint32_t a_frame, bool a_wantFilename, BSFixedString& a_stackFrame) override;					 // 03
		void DumpPersistenceInformationToLog(const char* a_logfile, ObjectHandle a_objectHandle) const override;									 // 04
		void DumpEventRelayInformationToLog(const char* a_logfile, ObjectHandle a_objectHandle, const BSFixedString& a_propertyName) const override; // 05

		[[nodiscard]] bool IsStackRunning(StackID a_stackId) const;

		// members
		ErrorLogger* errorLogger;													   // 0080
		IMemoryPagePolicy* memoryPagePolicy;										   // 0088
		IObjectHandlePolicy* handlePolicy;											   // 0090
		ObjectBindPolicy* objectBindPolicy;											   // 0098
		IClientVM* clientVM;														   // 00A0
		IStackCallbackSaveInterface* stackCallbackSaveInterface;					   // 00A8
		IProfilePolicy* profilePolicy;												   // 00B0
		ISavePatcherInterface* savePatcherInterface;								   // 00B8
		mutable BSSpinLock typeInfoLock;											   // 00C0
		LinkerProcessor linker;														   // 00C8
		BSTHashMap<BSFixedString, BSTSmartPointer<ObjectTypeInfo>> objectTypeMap;	   // 0168
		BSTHashMap<BSFixedString, BSTSmartPointer<StructTypeInfo>> structTypeMap;	   // 0198
		BSTHashMap<FormType, BSFixedString> typeIDToObjectType;						   // 01C8
		BSTHashMap<BSFixedString, FormType> objectTypeToTypeID;						   // 01F8
		BSTArray<BSTSmartPointer<ObjectTypeInfo>> typesToUnload;					   // 0228
		mutable BSSpinLock funcQueueLock;											   // 0240
		BSTStaticFreeList<FunctionMessage, 0x400> funcMsgPool;						   // 0248
		BSTCommonLLMessageQueue<FunctionMessage> funcMsgQueue;						   // 8260
		BSTArray<FunctionMessage> overflowFuncMsgs;									   // 8288
		BSTArray<CodeTasklet*> vmTasks;												   // 82A0
		std::uint32_t waitingFunctionMsgs;											   // 82B8
		bool overstressed;															   // 82BC
		bool initialized;															   // 82BD
		std::array<std::byte, 0xBD00 - 0x82BE> pad82BE;								   // 82BE
		BSTArray<SuspendedStack> overflowSuspendArray01;							   // BD00
		BSTArray<SuspendedStack> overflowSuspendArray02;							   // BD18
		mutable BSSpinLock suspendQueueLock;										   // BD30
		std::array<std::byte, 0xBD40 - 0xBD38> padBD38;								   // BD38
		BSTArray<SuspendedStack>* stacksToResumeOverflow;							   // BD40
		std::array<std::byte, 0xBD50 - 0xBD48> padBD48;								   // BD48
		BSTArray<SuspendedStack>* stacksToSuspendOverflow;							   // BD50
		mutable BSSpinLock runningStacksLock;										   // BD58
		BSTHashMap<StackID, BSTSmartPointer<Stack>> allRunningStacks;				   // BD60
		BSTHashMap<StackID, BSTSmartPointer<Stack>> waitingLatentReturns;			   // BD90
		StackID nextStackID;														   // BDC0
		mutable BSSpinLock frozenStacksLock;										   // BDC4
		std::array<std::byte, 0xBDD0 - 0xBDCC> padBDCC;								   // BDCC
		BSTArray<msvc::unique_ptr<PendingLatentReturn>> pendingLatentReturns;		   // BDD0
		BSTSmartPointer<BSScript::Stack> frozenStacksHead;							   // BDE8
		std::uint32_t frozenStacksCount;											   // BDF0
		REX::Enum<FreezeState, std::int32_t> freezeState;							   // BDF4
		mutable BSSpinLock attachedScriptsLock;										   // BDF8
		BSTHashMap<ObjectHandle, BSTSmallSharedArray<AttachedScript>> attachedScripts; // BE00
		std::uint32_t nextObjectToClean;											   // BE30
		std::array<std::byte, 0xBE38 - 0xBE34> padBE34;								   // BE34
		ObjectHandle nextAttachedObjectToClean;										   // BE38
		BSTArray<BSTSmartPointer<Object>> detachedScripts;							   // BE40
		mutable BSSpinLock structsLock;												   // BE58
		std::uint32_t nextStructToClean;											   // BE60
		std::array<std::byte, 0xBE68 - 0xBE64> padBE64;								   // BE64
		BSTArray<BSTSmartPointer<Struct>> allStructs;								   // BE68
		mutable BSSpinLock arraysLock;												   // BE80
		std::uint32_t nextArrayToClean;												   // BE88
		std::array<std::byte, 0xBE90 - 0xBE8C> padBE8C;								   // BE8C
		BSTArray<BSTSmartPointer<Array>> arrays;									   // BE90
		mutable BSSpinLock objectResetLock;											   // BEA8
		BSTArray<BSTSmartPointer<Object>> objectsAwaitingReset;						   // BEB0
		mutable BSSpinLock loadTableLock;											   // BEC8
		BSTHashMap<ObjectHandle, BSTSmartPointer<Object>> loadTable;				   // BED0
		BSTHashMap<ObjectHandle, ObjectHandle> loadHandlesTable;					   // BF00
		BSTHashMap<ObjectHandle, BSTSmartPointer<Struct>> structLoadTable;			   // BF30
		BSTHashMap<ObjectHandle, LoadedArrayEntry> arrayLoadTable;					   // BF60
		mutable BSSpinLock queuedUnbindLock;										   // BF90
		BSTArray<QueuedUnbindRefs> queuedUnbinds;									   // BF98
		mutable BSSpinLock eventRelayLock;											   // BFB0
		BSTHashMap<ObjectHandle, BSTSmartPointer<EventRelay>> eventRelays;			   // BFB8
		std::uint16_t currentSaveGameVersion;										   // BFE8
		std::array<std::byte, 0xBFEC - 0xBFEA> padBFEA;								   // BFEA
		std::uint32_t saveObjectCount;												   // BFEC
		std::uint32_t saveStructCount;												   // BFF0
		std::uint32_t saveArrayCount;												   // BFF4
		WritableStringTable writableStringTable;									   // BFF8
		ReadableStringTable readableStringTable;									   // C010
		WritableTypeTable writableTypeTable;										   // C028
		ReadableTypeTable readableTypeTable;										   // C038
		std::array<std::byte, 0xC080 - 0xC040> padC040;								   // C040
	};
	static_assert(sizeof(VirtualMachine) == 0xC080);
}
