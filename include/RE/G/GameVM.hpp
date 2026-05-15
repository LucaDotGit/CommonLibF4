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
	class __declspec(novtable) GameVM
		: public BSScript::IClientVM,						   // 00
		  public BSScript::IStackCallbackSaveInterface,		   // 08
		  public BSTEventSink<BSScript::StatsEvent>,		   // 10
		  public BSTEventSink<InputEnableLayerDestroyedEvent>, // 18
		  public BSTEventSink<PositionPlayerEvent>,			   // 20
		  public BSTEventSink<TESFormDeleteEvent>,			   // 28
		  public BSTEventSink<TESFormIDRemapEvent>,			   // 30
		  public BSTEventSink<TESInitScriptEvent>,			   // 37
		  public BSTEventSink<TESResolveNPCTemplatesEvent>,	   // 40
		  public BSTEventSink<TESUniqueIDChangeEvent>,		   // 48
		  public BSTSingletonSDM<GameVM>,					   // 50
		  public BSTEventSource<GameScript::StatsEvent>		   // 58
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameVM };
		inline static constexpr auto VTABLE{ VTABLE::GameVM };

		using Milliseconds = std::chrono::duration<REX::Float32, std::chrono::milliseconds::period>;

#define RUNTIME_DATA_CONTENT                                                                                  \
	GameScript::SavePatcher savePatcher;														   /* 0600 */ \
	mutable BSSpinLock freezeLock;																   /* 0608 */ \
	bool frozen;																				   /* 0610 */ \
	mutable BSSpinLock vmTimeLock;																   /* 0614 */ \
	std::uint32_t currentTime;																	   /* 061C */ \
	std::uint32_t currentMenuModeTime;															   /* 0620 */ \
	std::uint32_t currentGameTime;																   /* 0624 */ \
	bool updateHasBeenRun;																		   /* 0628 */ \
	bool saveLoad;																				   /* 0629 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> renderSafeFunctorPool01;   /* 0630 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> renderSafeFunctorQueue01;   /* 2648 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> renderSafeFunctorPool02;   /* 2670 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> renderSafeFunctorQueue02;   /* 4688 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> postRenderFunctorPool01;   /* 46B0 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> postRenderFunctorQueue01;   /* 66C8 */ \
	BSTStaticFreeList<BSTSmartPointer<GameScript::DelayFunctor>, 0x200> postRenderFunctorPool02;   /* 66F0 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>> postRenderFunctorQueue02;   /* 8708 */ \
	mutable BSSpinLock renderSafeQueueLock;														   /* 8730 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* renderSafeQueueToReadFrom; /* 8738 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* renderSafeQueueToWriteTo;  /* 8740 */ \
	mutable BSSpinLock postRenderQueueLock;														   /* 8748 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* postRenderQueueToReadFrom; /* 8750 */ \
	BSTCommonLLMessageQueue<BSTSmartPointer<GameScript::DelayFunctor>>* postRenderQueueToWriteTo;  /* 8758 */ \
	mutable BSSpinLock userLogLock;																   /* 8760 */ \
	BSTHashMap<BSFixedString, BSScript::ErrorLogger*> userLogs;									   /* 8768 */ \
	mutable BSSpinLock statsWarningLock;														   /* 8798 */ \
	std::uint32_t initialSuspendOverageTime;													   /* 87A0 */ \
	std::uint32_t initialRunningOverageTime;													   /* 87A4 */ \
	std::uint32_t initialStackMemoryOverageTime;												   /* 87A8 */ \
	std::uint32_t lastWarningTime;																   /* 87AC */ \
	std::uint32_t overflowFlags;																   /* 87B0 */

		class RuntimeData
		{
		public:
			// members
			RUNTIME_DATA_CONTENT;
		};

		~GameVM() override; // 00

		// override (BSScript::IClientVM)
		bool IsVMFrozen() const override; // 01
		void PreSave() override;		  // 02

		// override (BSScript::IStackCallbackSaveInterface)
		bool SaveStackCallback(BSStorage& a_buffer, const BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor) const override;				  // 01
		bool LoadStackCallback(const BSStorage& a_buffer, bool& a_unk01, BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor) const override; // 02

		// override (BSTEventSink<BSScript::StatsEvent>)
		BSEventNotifyControl ProcessEvent(const BSScript::StatsEvent& a_event, BSTEventSource<BSScript::StatsEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<InputEnableLayerDestroyedEvent>)
		BSEventNotifyControl ProcessEvent(const InputEnableLayerDestroyedEvent& a_event, BSTEventSource<InputEnableLayerDestroyedEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<PositionPlayerEvent>)
		BSEventNotifyControl ProcessEvent(const PositionPlayerEvent& a_event, BSTEventSource<PositionPlayerEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESFormDeleteEvent>)
		BSEventNotifyControl ProcessEvent(const TESFormDeleteEvent& a_event, BSTEventSource<TESFormDeleteEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESFormIDRemapEvent>)
		BSEventNotifyControl ProcessEvent(const TESFormIDRemapEvent& a_event, BSTEventSource<TESFormIDRemapEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESInitScriptEvent>)
		BSEventNotifyControl ProcessEvent(const TESInitScriptEvent& a_event, BSTEventSource<TESInitScriptEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESResolveNPCTemplatesEvent>)
		BSEventNotifyControl ProcessEvent(const TESResolveNPCTemplatesEvent& a_event, BSTEventSource<TESResolveNPCTemplatesEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESUniqueIDChangeEvent>)
		BSEventNotifyControl ProcessEvent(const TESUniqueIDChangeEvent& a_event, BSTEventSource<TESUniqueIDChangeEvent>* a_eventSource) override; // 01

		[[nodiscard]] static GameVM* GetSingleton();

		[[nodiscard]] static BSTSmartPointer<BSScript::IVirtualMachine> GetVMInterface();
		[[nodiscard]] static BSTSmartPointer<BSScript::Internal::VirtualMachine> GetInternalVM();

		[[nodiscard]] RuntimeData& GetRuntimeData() noexcept;
		[[nodiscard]] const RuntimeData& GetRuntimeData() const noexcept;

		[[nodiscard]] Milliseconds GetCurrentTime() const noexcept;
		[[nodiscard]] Milliseconds GetCurrentMenuModeTime() const noexcept;
		[[nodiscard]] Milliseconds GetCurrentGameTime() const noexcept;

		bool QueuePostRenderCall(const BSTSmartPointer<GameScript::DelayFunctor>& a_functor);
		void RegisterForAllGameEvents();
		void SendEventToObjectAndRelated(
			BSScript::ObjectHandle a_object,
			const BSFixedString& a_eventName,
			const BSTThreadScrapFunction<bool(BSScrapArray<BSScript::Variable>&)>& a_args,
			const BSTThreadScrapFunction<bool(const BSTSmartPointer<BSScript::Object>&)>& a_filter,
			const BSTSmartPointer<BSScript::IStackCallbackFunctor>& a_callbackFunctor);

		// members
		BSTSmartPointer<BSScript::IVirtualMachine> impl;		// 00B0
		BSScript::IVMSaveLoadInterface* saveLoadInterface;		// 00B8
		BSScript::IVMDebugInterface* debugInterface;			// 00C0
		BSScript::SimpleAllocMemoryPagePolicy memoryPagePolicy; // 00C8
		BSScript::CompiledScriptLoader scriptLoader;			// 00F8
		GameScript::Logger logger;								// 0130
		GameScript::HandlePolicy handlePolicy;					// 01E0
		GameScript::ObjectBindPolicy objectBindPolicy;			// 0288
		BSTSmartPointer<BSScript::IStore> scriptStore;			// 0360
		GameScript::FragmentSystem fragmentSystem;				// 0368
		GameScript::Profiler profiler;							// 04F0
#if COMMONLIB_RUNTIME_AE == 0
		RUNTIME_DATA_CONTENT // 05F0
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
		RUNTIME_DATA_CONTENT // 0600
#endif
	};
#if COMMONLIB_RUNTIME_AE == 0
	static_assert(sizeof(GameVM) == 0x87A8);
	static_assert(offsetof(GameVM, savePatcher) == 0x05F0);
#elif COMMONLIB_RUNTIME_VR == 0 && COMMONLIB_RUNTIME_OG == 0 && COMMONLIB_RUNTIME_NG == 0
	static_assert(sizeof(GameVM) == 0x87B8);
	static_assert(offsetof(GameVM, savePatcher) == 0x0600);
#else
	static_assert(sizeof(GameVM) == 0x05D0);
#endif
}

#undef RUNTIME_DATA_CONTENT
