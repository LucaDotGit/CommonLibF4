#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSPointerHandle.hpp"
#include "RE/B/BSTArray.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/C/CameraStates.hpp"
#include "RE/H/hkRefPtr.hpp"
#include "RE/H/hknpBodyId.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESCamera.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE::Impl
{
	template <class T>
	concept PlayerCameraStateConstraint =
		std::derived_from<T, TESCameraState> &&
		!std::is_pointer_v<T> &&
		!std::is_reference_v<T> &&
		std::same_as<std::remove_cv_t<decltype(T::CAMERA_STATE)>, CameraStates>;
}

namespace RE
{
	class hknpBSWorld;
	class hknpShape;
	class IdleInputEvent;
	class OtherEventEnabledEvent;
	class UserEventEnabledEvent;

	class __declspec(novtable) PlayerCamera
		: public TESCamera,							   // 00
		  public BSInputEventReceiver,				   // 38
		  public BSTEventSink<IdleInputEvent>,		   // 48
		  public BSTEventSink<UserEventEnabledEvent>,  // 50
		  public BSTEventSink<OtherEventEnabledEvent>, // 58
		  public BSTSingletonSDM<PlayerCamera>		   // 60
	{
	public:
		inline static constexpr auto RTTI{ RTTI::PlayerCamera };
		inline static constexpr auto VTABLE{ VTABLE::PlayerCamera };

		~PlayerCamera() override; // 00

		// override (TESCamera)
		void SetCameraRoot(NiNode* a_cameraRoot) override; // 01
		void SetEnabled(bool a_enabled) override;		   // 02
		void Update() override;							   // 03

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 00

		// override (BSTEventSink<IdleInputEvent>)
		BSEventNotifyControl ProcessEvent(const IdleInputEvent& a_event, BSTEventSource<IdleInputEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<UserEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const UserEventEnabledEvent& a_event, BSTEventSource<UserEventEnabledEvent>* a_eventSource) override; // 01

		// override (BSTEventSink<OtherEventEnabledEvent>)
		BSEventNotifyControl ProcessEvent(const OtherEventEnabledEvent& a_event, BSTEventSource<OtherEventEnabledEvent>* a_eventSource) override; // 01

		[[nodiscard]] static PlayerCamera* GetSingleton();

		[[nodiscard]] bool IsStateActive(CameraStates a_state) const noexcept;
		[[nodiscard]] bool IsStateActive(const BSTSmartPointer<TESCameraState>& a_state) const noexcept;

		[[nodiscard]] BSTSmartPointer<TESCameraState> GetState(CameraStates a_state) const;
		[[nodiscard]] BSTSmartPointer<TESCameraState> GetState() const;

		void SetState(TESCameraState* a_newState);
		void SetState(const BSTSmartPointer<TESCameraState>& a_newState);

		void ToggleFreeCameraMode(bool a_freezeTime);
		void StartPipboyMode(bool a_forcePipboyModeCamera);
		void StopPipboyMode();

		template <Impl::PlayerCameraStateConstraint T>
		[[nodiscard]] BSTSmartPointer<T> GetState()
		{
			auto& state = cameraStates[T::CAMERA_STATE];
			return { state ? static_cast<T*>(state.get()) : nullptr };
		}

		// members
		ActorHandle cameraTarget;																				   // 064
		BSTSmallArray<BSTSmartPointer<TESCameraState>, std::to_underlying(CameraStates::kTotal)> tempReturnStates; // 068
		std::array<BSTSmartPointer<TESCameraState>, std::to_underlying(CameraStates::kTotal)> cameraStates;		   // 0E0
		hknpBodyId cameraBodyID;																				   // 148
		hkRefPtr<hknpShape> cameraShape;																		   // 150
		hkRefPtr<hknpBSWorld> physicsWorld;																		   // 158
		ActorHandle savedCollidedActor;																			   // 160
		ObjectRefHandle collisionIgnoredReference;																   // 164
		REX::Float32 worldFOV;																					   // 168
		REX::Float32 firstPersonFOV;																			   // 16C
		REX::Float32 fovAdjustCurrent;																			   // 170
		REX::Float32 fovAdjustTarget;																			   // 174
		REX::Float32 fovAdjustPerSec;																			   // 178
		REX::Float32 fovAnimatorAdjust;																			   // 17C
		REX::Float32 collisionDistPercent;																		   // 180
		REX::Float32 curPlayerVisible;																			   // 184
		NiPoint3 bufferedCameraPos;																				   // 188
		REX::Float32 heading;																					   // 194
		REX::Float32 timeInPitchZero;																			   // 198
		REX::Float32 originalPitchToZero;																		   // 19C
		std::uint32_t furnitureCollisionGroup;																	   // 1A0
		bool allowAutoVanityMode;																				   // 1A4
		bool bowZoomedIn;																						   // 1A5
		bool freeRotationReady;																					   // 1A6
		bool cameraPosBuffered;																					   // 1A7
		bool zeroOutPitch;																						   // 1A8
		bool adjustFOV;																							   // 1A9
		bool trailerCameraMode;																					   // 1AA
		bool pipboyMode;																						   // 1AB
		bool savedFadeOutCloseActors;																			   // 1AC
	};
	static_assert(sizeof(PlayerCamera) == 0x1B0);
}
