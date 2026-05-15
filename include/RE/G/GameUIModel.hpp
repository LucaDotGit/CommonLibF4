#pragma once

#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/F/FaderMenuDisplayState.hpp"
#include "RE/S/SaveLoadMessageStringEvent.hpp"

namespace RE
{
	enum class SaveLoadMessageType : std::int32_t;

	class ColorUpdateEvent;
	class DoBeforeNewOrLoadCompletedEvent;
	class QueueSurvivalBumpDownMessage;
	class RevertPlayerCharacterEvent;
	class SaveLoadMessageStringEvent;
	class SaveLoadMessageTypeEvent;

	class __declspec(novtable) GameUIModel
		: public BSTEventSink<ColorUpdateEvent>,				// 00
		  public BSTEventSink<RevertPlayerCharacterEvent>,		// 08
		  public BSTEventSink<DoBeforeNewOrLoadCompletedEvent>, // 10
		  public BSTEventSink<SaveLoadMessageTypeEvent>,		// 18
		  public BSTEventSink<QueueSurvivalBumpDownMessage>,	// 20
		  public BSTSingletonSDM<GameUIModel>					// 28
	{
	public:
		inline static constexpr auto RTTI{ RTTI::GameUIModel };
		inline static constexpr auto VTABLE{ VTABLE::GameUIModel };

		class UICountdownTimer
		{
		public:
			// members
			std::int64_t startTime; // 00
			std::int64_t endTime;	// 08
			bool isActive;			// 10
		};
		static_assert(sizeof(UICountdownTimer) == 0x18);

		~GameUIModel() override; // 00

		// override (BSTEventSink<ColorUpdateEvent>)
		BSEventNotifyControl ProcessEvent(const ColorUpdateEvent& a_event, BSTEventSource<ColorUpdateEvent>* a_eventSource) override; // 00

		// override (BSTEventSink<RevertPlayerCharacterEvent>)
		BSEventNotifyControl ProcessEvent(const RevertPlayerCharacterEvent& a_event, BSTEventSource<RevertPlayerCharacterEvent>* a_eventSource) override; // 00

		// override (BSTEventSink<DoBeforeNewOrLoadCompletedEvent>)
		BSEventNotifyControl ProcessEvent(const DoBeforeNewOrLoadCompletedEvent& a_event, BSTEventSource<DoBeforeNewOrLoadCompletedEvent>* a_eventSource) override; // 00

		// override (BSTEventSink<SaveLoadMessageTypeEvent>)
		BSEventNotifyControl ProcessEvent(const SaveLoadMessageTypeEvent& a_event, BSTEventSource<SaveLoadMessageTypeEvent>* a_eventSource) override; // 00

		// override (BSTEventSink<QueueSurvivalBumpDownMessage>)
		BSEventNotifyControl ProcessEvent(const QueueSurvivalBumpDownMessage& a_event, BSTEventSource<QueueSurvivalBumpDownMessage>* a_eventSource) override; // 00

		[[nodiscard]] static GameUIModel* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<GameUIModel**>{ ID::GameUIModel::Singleton };
			return *SINGLETON;
		}

		void SetGameColors()
		{
			using FuncType = decltype(&GameUIModel::SetGameColors);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GameUIModel::SetGameColors };
			std::invoke(FUNC, this);
		}

		void UpdateDataModels()
		{
			using FuncType = decltype(&GameUIModel::UpdateDataModels);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::GameUIModel::UpdateDataModels };
			std::invoke(FUNC, this);
		}

		// members
		BSTValueEventSource<SaveLoadMessageStringEvent> saveLoadMessage; // 30
		BSTValueEventSink<FaderMenuDisplayState> faderDisplayState;		 // 58
		BSTOptional<SaveLoadMessageType> saveLoadMessageType;			 // 80
		UICountdownTimer saveLoadMessageDisplayTimer;					 // 88
		std::int32_t survivalBumpDownMessageDelayCount;					 // A0
	};
	static_assert(sizeof(GameUIModel) == 0xA8);
}
