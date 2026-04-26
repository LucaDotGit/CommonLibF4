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

	class __declspec(novtable) PlayerControls
		: public BSInputEventReceiver,					 // 000
		  public BSTEventSink<MenuOpenCloseEvent>,		 // 010
		  public BSTEventSink<MenuModeChangeEvent>,		 // 018
		  public BSTEventSink<TESFurnitureEvent>,		 // 020
		  public BSTEventSink<UserEventEnabledEvent>,	 // 028
		  public IMovementPlayerControls,				 // 030
		  public BSTEventSink<QuickContainerStateEvent>, // 038
		  public BSTSingletonSDM<PlayerControls>		 // 040
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PlayerControls };
		inline static constexpr auto VTABLE{ VTABLE::PlayerControls };

		enum class LERP_GRAPH : std::int32_t
		{
			kMovementThird = 0,
			kMovementFirst = 1,
			kLooking = 2
		};

		~PlayerControls() override; // 00

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 01

		// override (BSTEventSink<MenuOpenCloseEvent>)
		BSEventNotifyControl ProcessEvent(const MenuOpenCloseEvent& a_event, BSTEventSource<MenuOpenCloseEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<MenuModeChangeEvent>)
		BSEventNotifyControl ProcessEvent(const MenuModeChangeEvent& a_event, BSTEventSource<MenuModeChangeEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<TESFurnitureEvent>)
		BSEventNotifyControl ProcessEvent(const TESFurnitureEvent& a_event, BSTEventSource<TESFurnitureEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<UserEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent& a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource) override; // 01

		// override (IMovementPlayerControls)
		void GetControllerOutput(std::uint32_t a_numericID, PlayerControlsMovementData& a_normalizedOutputData) override; // 01

		// override (BSTEventSink<QuickContainerStateEvent>)
		BSEventNotifyControl ProcessEvent(const QuickContainerStateEvent& a_event, BSTEventSource<QuickContainerStateEvent>* a_eventSource) override; // 01

		[[nodiscard]] static PlayerControls* GetSingleton();

		bool CanPerformAction(DEFAULT_OBJECT a_action);
		bool DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority);
		void RegisterHandler(PlayerInputHandler* a_handler);
		void RegisterHandler(HeldStateHandler* a_handler);

		// members
		PlayerControlsData data;												// 044
		BSTArray<PlayerInputHandler*> handlers;									// 090
		BSTArray<HeldStateHandler*> heldStateHandlers;							// 0A8
		std::array<std::uint32_t, 3> topGraphPoint;								// 0C0
		std::array<std::array<std::array<REX::Float32, 10>, 2>, 3> graphPoints; // 0CC
		BSTArray<ActorHandle> actionInterestedActors;							// 1C0
		mutable BSSpinLock actorArraySpinLock;									// 1D8
		MovementHandler* movementHandler;										// 1E0
		LookHandler* lookHandler;												// 1E8
		SprintHandler* sprintHandler;											// 1F0
		ReadyWeaponHandler* readyWeaponHandler;									// 1F8
		AutoMoveHandler* autoMoveHandler;										// 200
		ToggleRunHandler* toggleRunHandler;										// 208
		ActivateHandler* activateHandler;										// 210
		JumpHandler* jumpHandler;												// 218
		AttackBlockHandler* attackHandler;										// 220
		RunHandler* runHandler;													// 228
		SneakHandler* sneakHandler;												// 230
		TogglePOVHandler* togglePOVHandler;										// 238
		MeleeThrowHandler* meleeThrowHandler;									// 240
		GrabRotationHandler* grabRotationHandler;								// 248
		bool notifyingHandlers;													// 250
		bool blockPlayerInput;													// 251
		REX::Float32 cameraAutoRotationX;										// 254
		REX::Float32 cameraAutoRotationY;										// 258
	};
	static_assert(sizeof(PlayerControls) == 0x260);
}
