#pragma once

#include "RE/A/ActionInput.hpp"
#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/H/HeldStateHandler.hpp"
#include "RE/I/IMovementPlayerControls.hpp"
#include "RE/P/PlayerInputHandler.hpp"

namespace RE
{
	enum class DEFAULT_OBJECT : std::int32_t;

	class ActivateHandler;
	class AttackBlockHandler;
	class AutoMoveHandler;
	class GrabRotationHandler;
	class JumpHandler;
	class LookHandler;
	class MeleeThrowHandler;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class MovementHandler;
	class QuickContainerStateEvent;
	class ReadyWeaponHandler;
	class RunHandler;
	class SneakHandler;
	class SprintHandler;
	class TogglePOVHandler;
	class ToggleRunHandler;
	class UserEventEnabledEvent;
	class TESFurnitureEvent;

	class __declspec(novtable) PlayerControls :
		public BSInputEventReceiver,				   // 0x000
		public BSTEventSink<MenuOpenCloseEvent>,	   // 0x010
		public BSTEventSink<MenuModeChangeEvent>,	   // 0x018
		public BSTEventSink<TESFurnitureEvent>,		   // 0x020
		public BSTEventSink<UserEventEnabledEvent>,	   // 0x028
		public IMovementPlayerControls,				   // 0x030
		public BSTEventSink<QuickContainerStateEvent>, // 0x038
		public BSTSingletonSDM<PlayerControls>		   // 0x040
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PlayerControls;
		inline static constexpr const auto& VTABLE = VTABLE::PlayerControls;

		enum class LERP_GRAPH : std::int32_t
		{
			MovementThird = 0,
			MovementFirst = 1,
			Looking = 2
		};

		~PlayerControls() override; // 0x00

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		auto ProcessEvent(
			const MenuOpenCloseEvent& a_event,
			BSTEventSource<MenuOpenCloseEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<MenuModeChangeEvent>)
		auto ProcessEvent(
			const MenuModeChangeEvent& a_event,
			BSTEventSource<MenuModeChangeEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<TESFurnitureEvent>)
		auto ProcessEvent(
			const TESFurnitureEvent& a_event,
			BSTEventSource<TESFurnitureEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<UserEventEnabledEvent>)
		auto ProcessEvent(
			const UserEventEnabledEvent& a_event,
			BSTEventSource<UserEventEnabledEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (IMovementPlayerControls)
		void GetControllerOutput(std::uint32_t a_numericID, PlayerControlsMovementData& a_normalizedOutputData)
			override; // 0x01

		// override (BSTEventSink<QuickContainerStateEvent>)
		auto ProcessEvent(
			const QuickContainerStateEvent& a_event,
			BSTEventSource<QuickContainerStateEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> PlayerControls*;

		auto CanPerformAction(DEFAULT_OBJECT a_action) -> bool;
		auto DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority) -> bool;
		void RegisterHandler(PlayerInputHandler* a_handler);
		void RegisterHandler(HeldStateHandler* a_handler);

		// members
		PlayerControlsData data;												// 0x044
		BSTArray<PlayerInputHandler*> handlers;									// 0x090
		BSTArray<HeldStateHandler*> heldStateHandlers;							// 0x0A8
		std::array<std::uint32_t, 3> topGraphPoint;								// 0x0C0
		std::array<std::array<std::array<REX::Float32, 10>, 2>, 3> graphPoints; // 0x0CC
		BSTArray<ActorHandle> actionInterestedActors;							// 0x1C0
		mutable BSSpinLock actorArraySpinLock;									// 0x1D8
		MovementHandler* movementHandler;										// 0x1E0
		LookHandler* lookHandler;												// 0x1E8
		SprintHandler* sprintHandler;											// 0x1F0
		ReadyWeaponHandler* readyWeaponHandler;									// 0x1F8
		AutoMoveHandler* autoMoveHandler;										// 0x200
		ToggleRunHandler* toggleRunHandler;										// 0x208
		ActivateHandler* activateHandler;										// 0x210
		JumpHandler* jumpHandler;												// 0x218
		AttackBlockHandler* attackHandler;										// 0x220
		RunHandler* runHandler;													// 0x228
		SneakHandler* sneakHandler;												// 0x230
		TogglePOVHandler* togglePOVHandler;										// 0x238
		MeleeThrowHandler* meleeThrowHandler;									// 0x240
		GrabRotationHandler* grabRotationHandler;								// 0x248
		bool notifyingHandlers;													// 0x250
		bool blockPlayerInput;													// 0x251
		REX::Float32 cameraAutoRotationX;										// 0x254
		REX::Float32 cameraAutoRotationY;										// 0x258
	};

	static_assert(sizeof(PlayerControls) == 0x260);
}
