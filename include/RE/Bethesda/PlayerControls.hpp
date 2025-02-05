#pragma once

#include "RE/Bethesda/BSInputEventReceiver.hpp"
#include "RE/Bethesda/BSInputEventUser.hpp"
#include "RE/Bethesda/BSPointerHandle.hpp"
#include "RE/Bethesda/BSSpring.hpp"
#include "RE/Bethesda/BSTArray.hpp"
#include "RE/Bethesda/BSTEvent.hpp"
#include "RE/Bethesda/BSTSingleton.hpp"
#include "RE/Bethesda/IMovementInterface.hpp"
#include "RE/NetImmerse/NiPoint.hpp"

namespace RE
{
	class BGSAction;
	class MenuModeChangeEvent;
	class MenuOpenCloseEvent;
	class QuickContainerStateEvent;
	class UserEventEnabledEvent;

	struct ActivateHandler;
	struct GrabRotationHandler;
	struct MovementHandler;
	struct RunHandler;
	struct SprintHandler;
	struct TESFurnitureEvent;
	struct TogglePOVHandler;
	struct ToggleRunHandler;

	class __declspec(novtable) ActionInput
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ActionInput };
		inline static constexpr auto VTABLE{ VTABLE::ActionInput };

		enum class ACTIONPRIORITY
		{
			kImperative,
			kQueue,
			kTry
		};

		struct Data
		{
		public:
			union
			{
				float f;
				std::int32_t i;
				std::uint32_t ui;
			}; // 00
		};

		virtual ~ActionInput(); // 00

		// members
		NiPointer<TESObjectREFR> ref;					   // 08
		NiPointer<TESObjectREFR> targetRef;				   // 10
		BGSAction* action;								   // 18
		REX::Enum<ACTIONPRIORITY, std::uint32_t> priority; // 20
		Data ActionData;								   // 24
	};
	static_assert(sizeof(ActionInput) == 0x28);

	struct PlayerControlsData
	{
	public:
		// members
		NiPoint2 moveInputVec;								 // 00
		NiPoint2 lookInputVec;								 // 08
		NiPoint2 lookInputVecNormalized;					 // 10
		NiPoint2 prevMoveVec;								 // 18
		NiPoint2 prevLookVec;								 // 20
		BSSpring::SpringState<NiPoint3> rotationSpeedSpring; // 28
		bool autoMove;										 // 44
		bool running;										 // 45
		bool togglePOV;										 // 46
		bool vanityModeEnabled;								 // 47
		bool checkHeldStates;								 // 48
		bool setupHeldStatesForRelease;						 // 49
	};
	static_assert(sizeof(PlayerControlsData) == 0x4C);

	class PlayerInputHandler
		: public BSInputEventUser // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PlayerInputHandler };
		inline static constexpr auto VTABLE{ VTABLE::PlayerInputHandler };

		explicit constexpr PlayerInputHandler(PlayerControlsData& a_data) noexcept :
			data(a_data)
		{
		}

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~PlayerInputHandler() = default; // 00

		// add
		virtual void PerFrameUpdate() { return; }; // 09

		// members
		PlayerControlsData& data;		// 10
		bool inQuickContainer{ false }; // 18
	};
	static_assert(sizeof(PlayerInputHandler) == 0x20);

	class AutoMoveHandler
		: public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AutoMoveHandler };
		inline static constexpr auto VTABLE{ VTABLE::AutoMoveHandler };

		explicit constexpr AutoMoveHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}
	};
	static_assert(sizeof(AutoMoveHandler) == 0x20);

	class HeldStateHandler
		: public PlayerInputHandler // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HeldStateHandler };
		inline static constexpr auto VTABLE{ VTABLE::HeldStateHandler };

		explicit constexpr HeldStateHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}

		// NOLINTNEXTLINE(modernize-use-override)
		virtual ~HeldStateHandler() = default; // 00

		// add
		virtual void UpdateHeldStateActive(const ButtonEvent* a_event) // 10
		{
			heldStateActive = a_event && (a_event->value != 0.0F || a_event->heldDownSecs < 0.0F);
		}

		virtual void SetHeldStateActive(bool a_flag) { heldStateActive = a_flag; } // 11

		// members
		bool heldStateActive{ false };	   // 20
		bool triggerReleaseEvent{ false }; // 21
	};
	static_assert(sizeof(HeldStateHandler) == 0x28);

	class AttackBlockHandler
		: public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::AttackBlockHandler };
		inline static constexpr auto VTABLE{ VTABLE::AttackBlockHandler };

		enum class POWER_ATTACK_STATE
		{
			kNone = 0,
			kLeft,
			kRight,
			kDual,
		};

		// members
		std::uint64_t dualAttackStartTime;								  // 28
		BSFixedString debounceEvent;									  // 30
		REX::Enum<POWER_ATTACK_STATE, std::uint32_t> checkForPowerAttack; // 38
		std::uint32_t numPowerAttacks;									  // 3C
		SettingT<INISettingCollection>* initialDelay;					  // 40
		SettingT<INISettingCollection>* subsequentDelay;				  // 48
		float attackTimer;												  // 50
		std::uint64_t rightAttackTimestamp;								  // 58
		float rightAttackHeldSeconds;									  // 60
		float rightAttackLastHeldSeconds;								  // 64
		float rightAttackLatchEngage;									  // 68
		float rightAttackLatchRelease;									  // 6C
		bool debounce;													  // 70
		bool castAttemptMade;											  // 71
		bool leftAttackButtonHeld;										  // 72
		bool rightAttackButtonHeld;										  // 73
		bool rightAttackQueued;											  // 74
		bool rightAttackPrevFrame;										  // 75
		bool setAttackTimer;											  // 76
		bool checkPostMeleeActions;										  // 77
		bool checkPostThrowActions;										  // 78
	};
	static_assert(sizeof(AttackBlockHandler) == 0x80);

	class JumpHandler
		: public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::JumpHandler };
		inline static constexpr auto VTABLE{ VTABLE::JumpHandler };

		explicit constexpr JumpHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}

		// members
		bool debounceAlternateExit{ false }; // 20
	};
	static_assert(sizeof(JumpHandler) == 0x28);

	class LookHandler
		: public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::LookHandler };
		inline static constexpr auto VTABLE{ VTABLE::LookHandler };

		explicit constexpr LookHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}

		// members
		float thumbstickMaxedSec{ 0.0f }; // 20
	};
	static_assert(sizeof(LookHandler) == 0x28);

	class MeleeThrowHandler
		: public HeldStateHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::MeleeThrowHandler };
		inline static constexpr auto VTABLE{ VTABLE::MeleeThrowHandler };

		// members
		bool buttonHoldDebounce; // 28
		bool pressRegistered;	 // 29
		bool queueThrow;		 // 2A
	};
	static_assert(sizeof(MeleeThrowHandler) == 0x30);

	class ReadyWeaponHandler
		: public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ReadyWeaponHandler };
		inline static constexpr auto VTABLE{ VTABLE::ReadyWeaponHandler };

		explicit constexpr ReadyWeaponHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}

		// members
		bool actionTaken{ false }; // 20
	};
	static_assert(sizeof(ReadyWeaponHandler) == 0x28);

	class SneakHandler
		: public PlayerInputHandler
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SneakHandler };
		inline static constexpr auto VTABLE{ VTABLE::SneakHandler };

		explicit constexpr SneakHandler(PlayerControlsData& a_data) noexcept :
			PlayerInputHandler(a_data)
		{
		}
	};
	static_assert(sizeof(SneakHandler) == 0x20);

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

		static PlayerControls* GetSingleton()
		{
			static REL::Relocation<PlayerControls**> singleton{ REL::RelocationID(544871, 2692013) };
			return *singleton;
		}

		bool CanPerformAction(DEFAULT_OBJECT a_action)
		{
			using func_t = decltype(&PlayerControls::CanPerformAction);
			static REL::Relocation<func_t> func{ REL::ID(565925) };
			return func(this, a_action);
		}

		bool DoAction(DEFAULT_OBJECT a_action, ActionInput::ACTIONPRIORITY a_priority)
		{
			using func_t = decltype(&PlayerControls::DoAction);
			static REL::Relocation<func_t> func{ REL::ID(818081) };
			return func(this, a_action, a_priority);
		}

		void RegisterHandler(PlayerInputHandler* a_handler) { DoRegisterHandler(a_handler, false); }
		void RegisterHandler(HeldStateHandler* a_handler) { DoRegisterHandler(a_handler, true); }

		// members
		PlayerControlsData data;					   // 044
		BSTArray<PlayerInputHandler*> handlers;		   // 090
		BSTArray<HeldStateHandler*> heldStateHandlers; // 0A8
		std::uint32_t topGraphPoint[3];				   // 0C0
		float graphPoints[3][10][2];				   // 0CC
		BSTArray<ActorHandle> actionInterestedActors;  // 1C0
		mutable BSSpinLock actorArraySpinLock;		   // 1D8
		MovementHandler* movementHandler;			   // 1E0
		LookHandler* lookHandler;					   // 1E8
		SprintHandler* sprintHandler;				   // 1F0
		ReadyWeaponHandler* readyWeaponHandler;		   // 1F8
		AutoMoveHandler* autoMoveHandler;			   // 200
		ToggleRunHandler* toggleRunHandler;			   // 208
		ActivateHandler* activateHandler;			   // 210
		JumpHandler* jumpHandler;					   // 218
		AttackBlockHandler* attackHandler;			   // 220
		RunHandler* runHandler;						   // 228
		SneakHandler* sneakHandler;					   // 230
		TogglePOVHandler* togglePOVHandler;			   // 238
		MeleeThrowHandler* meleeThrowHandler;		   // 240
		GrabRotationHandler* grabRotationHandler;	   // 248
		bool notifyingHandlers;						   // 250
		bool blockPlayerInput;						   // 251
		float cameraAutoRotationX;					   // 254
		float cameraAutoRotationY;					   // 258

	private:
		void DoRegisterHandler(PlayerInputHandler* a_handler, bool a_isHeldStateHandler)
		{
			using func_t = decltype(&PlayerControls::DoRegisterHandler);
			static REL::Relocation<func_t> func{ REL::RelocationID(177801, 2234822) };
			return func(this, a_handler, a_isHeldStateHandler);
		}
	};
	static_assert(sizeof(PlayerControls) == 0x260);
}
