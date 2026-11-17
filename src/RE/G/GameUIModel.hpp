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

	class __declspec(novtable) GameUIModel :
		public BSTEventSink<ColorUpdateEvent>,				  // 0x00
		public BSTEventSink<RevertPlayerCharacterEvent>,	  // 0x08
		public BSTEventSink<DoBeforeNewOrLoadCompletedEvent>, // 0x10
		public BSTEventSink<SaveLoadMessageTypeEvent>,		  // 0x18
		public BSTEventSink<QueueSurvivalBumpDownMessage>,	  // 0x20
		public BSTSingletonSDM<GameUIModel>					  // 0x28
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::GameUIModel;
		inline static constexpr const auto& VTABLE = VTABLE::GameUIModel;

		class UICountdownTimer
		{
		public:
			// members
			std::int64_t startTime; // 0x00
			std::int64_t endTime;	// 0x08
			bool isActive;			// 0x10
		};

		static_assert(sizeof(UICountdownTimer) == 0x18);

		~GameUIModel() override; // 0x00

		// override (BSTEventSink<ColorUpdateEvent>)
		auto ProcessEvent(
			const ColorUpdateEvent& a_event,
			BSTEventSource<ColorUpdateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x00

		// override (BSTEventSink<RevertPlayerCharacterEvent>)
		auto ProcessEvent(
			const RevertPlayerCharacterEvent& a_event,
			BSTEventSource<RevertPlayerCharacterEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x00

		// override (BSTEventSink<DoBeforeNewOrLoadCompletedEvent>)
		auto ProcessEvent(
			const DoBeforeNewOrLoadCompletedEvent& a_event,
			BSTEventSource<DoBeforeNewOrLoadCompletedEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x00

		// override (BSTEventSink<SaveLoadMessageTypeEvent>)
		auto ProcessEvent(
			const SaveLoadMessageTypeEvent& a_event,
			BSTEventSource<SaveLoadMessageTypeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x00

		// override (BSTEventSink<QueueSurvivalBumpDownMessage>)
		auto ProcessEvent(
			const QueueSurvivalBumpDownMessage& a_event,
			BSTEventSource<QueueSurvivalBumpDownMessage>* a_eventSource) -> BSEventNotifyControl override; // 0x00

		[[nodiscard]]
		static auto GetSingleton() noexcept -> GameUIModel*
		{
			static const auto SINGLETON = REL::Relocation<GameUIModel**>(ID::GameUIModel::Singleton);
			return *SINGLETON;
		}

		void SetGameColors()
		{
			using FuncType = decltype(&GameUIModel::SetGameColors);
			static const auto FUNC = REL::Relocation<FuncType>(ID::GameUIModel::SetGameColors);
			std::invoke(FUNC, this);
		}

		void UpdateDataModels()
		{
			using FuncType = decltype(&GameUIModel::UpdateDataModels);
			static const auto FUNC = REL::Relocation<FuncType>(ID::GameUIModel::UpdateDataModels);
			std::invoke(FUNC, this);
		}

		// members
		BSTValueEventSource<SaveLoadMessageStringEvent> saveLoadMessage; // 0x30
		BSTValueEventSink<FaderMenuDisplayState> faderDisplayState;		 // 0x58
		BSTOptional<SaveLoadMessageType> saveLoadMessageType;			 // 0x80
		UICountdownTimer saveLoadMessageDisplayTimer;					 // 0x88
		std::int32_t survivalBumpDownMessageDelayCount;					 // 0xA0
	};

	static_assert(sizeof(GameUIModel) == 0xA8);
}
