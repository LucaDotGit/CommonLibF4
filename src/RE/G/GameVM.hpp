#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/B/BSScript_CompiledScriptLoader.hpp"
#include "RE/B/BSScript_ErrorLogger.hpp"
#include "RE/B/BSScript_IClientVM.hpp"
#include "RE/B/BSScript_IStackCallbackSaveInterface.hpp"
#include "RE/B/BSScript_SimpleAllocMemoryPagePolicy.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTFreeList.hpp"
#include "RE/B/BSTHashMap.hpp"
#include "RE/B/BSTMessageQueue.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/B/BSTThreadScrapFunction.hpp"
#include "RE/G/GameScript_FragmentSystem.hpp"
#include "RE/G/GameScript_HandlePolicy.hpp"
#include "RE/G/GameScript_Logger.hpp"
#include "RE/G/GameScript_ObjectBindPolicy.hpp"
#include "RE/G/GameScript_Profiler.hpp"
#include "RE/G/GameScript_SavePatcher.hpp"
#include "RE/M/MemoryManager.hpp"

namespace RE
{
	class InputEnableLayerDestroyedEvent;
	class PositionPlayerEvent;
	class TESFormDeleteEvent;
	class TESFormIDRemapEvent;
	class TESInitScriptEvent;
	class TESResolveNPCTemplatesEvent;
	class TESUniqueIDChangeEvent;
}

namespace RE::BSScript
{
	class ErrorLogger;
	class IStackCallbackFunctor;
	class IVirtualMachine;
	class IVMDebugInterface;
	class IVMSaveLoadInterface;
	class StatsEvent;
	class Variable;
}

namespace RE::BSScript::Internal
{
	class VirtualMachine;
}

namespace RE::GameScript
{
	class DelayFunctor;
	class StatsEvent;
}

namespace RE
{
	class __declspec(novtable) GameVM :
		public BSScript::IClientVM,							 // 0x00
		public BSScript::IStackCallbackSaveInterface,		 // 0x08
		public BSTEventSink<BSScript::StatsEvent>,			 // 0x10
		public BSTEventSink<InputEnableLayerDestroyedEvent>, // 0x18
		public BSTEventSink<PositionPlayerEvent>,			 // 0x20
		public BSTEventSink<TESFormDeleteEvent>,			 // 0x28
		public BSTEventSink<TESFormIDRemapEvent>,			 // 0x30
		public BSTEventSink<TESInitScriptEvent>,			 // 0x37
		public BSTEventSink<TESResolveNPCTemplatesEvent>,	 // 0x40
		public BSTEventSink<TESUniqueIDChangeEvent>,		 // 0x48
		public BSTSingletonSDM<GameVM>,						 // 0x50
		public BSTEventSource<GameScript::StatsEvent>		 // 0x58
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameVM;
		inline static constexpr const auto& VTABLE = VTABLE::GameVM;

		using Milliseconds = std::chrono::duration<std::uint32_t, std::chrono::milliseconds::period>;

#define RUNTIME_DATA_CONTENT                                                                                  \
	GameScript::SavePatcher savePatcher;														   /* 0000 */ \
	mutable BSSpinLock freezeLock;																   /* 0008 */ \
	bool frozen;																				   /* 0010 */ \
	mutable BSSpinLock vmTimeLock;																   /* 0014 */ \
	Milliseconds currentTime;																	   /* 001C */ \
	Milliseconds currentMenuModeTime;															   /* 0020 */ \
	Milliseconds currentGameTime;																   /* 0024 */ \
	bool updateHasBeenRun;																		   /* 0028 */ \
	bool saveLoad;																				   /* 0029 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> renderSafeFunctorPool01;   /* 0030 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> renderSafeFunctorQueue01;   /* 2048 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> renderSafeFunctorPool02;   /* 2070 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> renderSafeFunctorQueue02;   /* 4088 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> postRenderFunctorPool01;   /* 40B0 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> postRenderFunctorQueue01;   /* 60C8 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> postRenderFunctorPool02;   /* 60F0 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> postRenderFunctorQueue02;   /* 8108 */ \
	mutable BSSpinLock renderSafeQueueLock;														   /* 8130 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* renderSafeQueueToReadFrom; /* 8138 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* renderSafeQueueToWriteTo;  /* 8140 */ \
	mutable BSSpinLock postRenderQueueLock;														   /* 8148 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* postRenderQueueToReadFrom; /* 8150 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* postRenderQueueToWriteTo;  /* 8158 */ \
	mutable BSSpinLock userLogLock;																   /* 8160 */ \
	BSTHashMap<BSFixedString, BSScript::ErrorLogger*> userLogs;									   /* 8168 */ \
	mutable BSSpinLock statsWarningLock;														   /* 8198 */ \
	Milliseconds initialSuspendOverageTime;														   /* 81A0 */ \
	Milliseconds initialRunningOverageTime;														   /* 81A4 */ \
	Milliseconds initialStackMemoryOverageTime;													   /* 81A8 */ \
	Milliseconds lastWarningTime;																   /* 81AC */ \
	std::uint32_t overflowFlags;																   /* 81B0 */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT; // 0x0000
		};

		static_assert(sizeof(RuntimeData) == 0x81B8);

		~GameVM() override; // 0x00

		// override (BSScript::IClientVM)
		auto IsVMFrozen() const -> bool override; // 0x01
		void PreSave() override;				  // 0x02

		// override (BSScript::IStackCallbackSaveInterface)
		auto SaveStackCallback(
			BSStorage& a_buffer,
			const BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor) const -> bool override; // 0x01
		auto LoadStackCallback(
			const BSStorage& a_buffer,
			bool& a_unk01,
			BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor) const -> bool override; // 0x02

		// override (BSTEventSink<BSScript::StatsEvent>)
		auto ProcessEvent(
			const BSScript::StatsEvent& a_event,
			BSTEventSource<BSScript::StatsEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<InputEnableLayerDestroyedEvent>)
		auto ProcessEvent(
			const InputEnableLayerDestroyedEvent& a_event,
			BSTEventSource<InputEnableLayerDestroyedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<PositionPlayerEvent>)
		auto ProcessEvent(
			const PositionPlayerEvent& a_event,
			BSTEventSource<PositionPlayerEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESFormDeleteEvent>)
		auto ProcessEvent(
			const TESFormDeleteEvent& a_event,
			BSTEventSource<TESFormDeleteEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESFormIDRemapEvent>)
		auto ProcessEvent(
			const TESFormIDRemapEvent& a_event,
			BSTEventSource<TESFormIDRemapEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESInitScriptEvent>)
		auto ProcessEvent(
			const TESInitScriptEvent& a_event,
			BSTEventSource<TESInitScriptEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESResolveNPCTemplatesEvent>)
		auto ProcessEvent(
			const TESResolveNPCTemplatesEvent& a_event,
			BSTEventSource<TESResolveNPCTemplatesEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESUniqueIDChangeEvent>)
		auto ProcessEvent(
			const TESUniqueIDChangeEvent& a_event,
			BSTEventSource<TESUniqueIDChangeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		GAME_HEAP_REDEFINE_NEW(GameVM);

		[[nodiscard]]
		static auto GetSingleton() noexcept -> GameVM*;

		[[nodiscard]]
		static auto GetVMInterface() noexcept -> BSTSmartPointer<BSScript::IVirtualMachine>;
		[[nodiscard]]
		static auto GetInternalVM() noexcept -> BSTSmartPointer<BSScript::Internal::VirtualMachine>;

		[[nodiscard]]
		auto GetRuntimeData() noexcept -> RuntimeData&;
		[[nodiscard]]
		auto GetRuntimeData() const noexcept -> const RuntimeData&;

		auto QueuePostRenderCall(const BSTSmartPointer<GameScript::DelayFunctor>& a_functor) -> bool;
		void RegisterForAllGameEvents();
		void SendEventToObjectAndRelated(
			BSScript::ObjectHandle a_object,
			const BSFixedString& a_eventName,
			const BSTThreadScrapFunction<bool(BSScrapArray<BSScript::Variable>&)>& a_args,
			const BSTThreadScrapFunction<bool(const BSTSmartPointer<BSScript::Object>&)>& a_filter,
			const BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor);

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> impl;		// 0x00B0
		BSScript::IVMSaveLoadInterface* saveLoadInterface;		// 0x00B8
		BSScript::IVMDebugInterface* debugInterface;			// 0x00C0
		BSScript::SimpleAllocMemoryPagePolicy memoryPagePolicy; // 0x00C8
		BSScript::CompiledScriptLoader scriptLoader;			// 0x00F8
		GameScript::Logger logger;								// 0x0130
		GameScript::HandlePolicy handlePolicy;					// 0x01E0
		GameScript::ObjectBindPolicy objectBindPolicy;			// 0x0288
		BSTSmartPointer<BSScript::IStore> scriptStore;			// 0x0360
		GameScript::FragmentSystem fragmentSystem;				// 0x0368
		GameScript::Profiler profiler;							// 0x04F0
#if (COMMONLIB_RUNTIME_AE == 0)
		RUNTIME_DATA_CONTENT; // 0x05F0
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
		RUNTIME_DATA_CONTENT; // 0x0600
#endif
	};

#if (COMMONLIB_RUNTIME_AE == 0)
	static_assert(sizeof(GameVM) == 0x8788);
#elif (COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0)
	static_assert(sizeof(GameVM) == 0x8788);
#else
	static_assert(sizeof(GameVM) == 0x05D0);
#endif
}

#undef RUNTIME_DATA_CONTENT
