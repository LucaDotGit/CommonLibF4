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
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESCamera.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE::Impl
{
	template <class T>
	concept PlayerCameraStateConstraint = std::derived_from<T, TESCameraState> &&
										  !REX::pointer<T> &&
										  !REX::reference<T> &&
										  std::same_as<std::remove_cv_t<decltype(T::CAMERA_STATE)>, CameraStates>;
}

namespace RE
{
	class hknpBSWorld;
	class hknpShape;
	class IdleInputEvent;
	class OtherEventEnabledEvent;
	class UserEventEnabledEvent;

	class __declspec(novtable) PlayerCamera :
		public TESCamera,							 // 0x00
		public BSInputEventReceiver,				 // 0x38
		public BSTEventSink<IdleInputEvent>,		 // 0x48
		public BSTEventSink<UserEventEnabledEvent>,	 // 0x50
		public BSTEventSink<OtherEventEnabledEvent>, // 0x58
		public BSTSingletonSDM<PlayerCamera>		 // 0x60
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::PlayerCamera;
		inline static constexpr const auto& VTABLE = VTABLE::PlayerCamera;

		~PlayerCamera() override; // 0x00

		// override (TESCamera)
		void SetCameraRoot(NiNode* a_cameraRoot) override; // 0x01
		void SetEnabled(bool a_enabled) override;		   // 0x02
		void Update() override;							   // 0x03

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 0x00

		// override (BSTEventSink<IdleInputEvent>)
		auto ProcessEvent(const IdleInputEvent& a_event, BSTEventSource<IdleInputEvent>* a_eventSource)
			-> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<UserEventEnabledEvent>)
		auto ProcessEvent(
			const UserEventEnabledEvent& a_event,
			BSTEventSource<UserEventEnabledEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		// override (BSTEventSink<OtherEventEnabledEvent>)
		auto ProcessEvent(
			const OtherEventEnabledEvent& a_event,
			BSTEventSource<OtherEventEnabledEvent>* a_eventSource) -> BSEventNotifyControl override; // 0x01

		[[nodiscard]]
		static auto GetSingleton() noexcept -> PlayerCamera*;

		[[nodiscard]]
		auto IsStateActive(CameraStates a_state) const noexcept -> bool;
		[[nodiscard]]
		auto IsStateActive(const BSTSmartPointer<TESCameraState>& a_state) const noexcept -> bool;

		[[nodiscard]]
		auto GetState(CameraStates a_state) const -> BSTSmartPointer<TESCameraState>;
		[[nodiscard]]
		auto GetState() const -> BSTSmartPointer<TESCameraState>;

		void SetState(TESCameraState* a_newState);
		void SetState(const BSTSmartPointer<TESCameraState>& a_newState);

		auto GetCameraPosition(NiPoint3& a_outPosition, bool a_addPlayerPos) const -> bool;
		void ToggleFreeCameraMode(bool a_freezeTime);
		void StartPipboyMode(bool a_forcePipboyModeCamera);
		void StopPipboyMode();

		template <Impl::PlayerCameraStateConstraint T>
		[[nodiscard]]
		auto GetState() -> BSTSmartPointer<T>
		{
			auto& state = cameraStates[T::CAMERA_STATE];
			return {state ? dynamic_pointer_cast<T>(state) : nullptr};
		}

		// members
		ActorHandle cameraTarget; // 0x064
		BSTSmallArray<BSTSmartPointer<TESCameraState>, std::to_underlying(CameraStates::_Count)>
			tempReturnStates;																				// 0x068
		std::array<BSTSmartPointer<TESCameraState>, std::to_underlying(CameraStates::_Count)> cameraStates; // 0x0E0
		hknpBodyId cameraBodyID;																			// 0x148
		hkRefPtr<hknpShape> cameraShape;																	// 0x150
		hkRefPtr<hknpBSWorld> physicsWorld;																	// 0x158
		ActorHandle savedCollidedActor;																		// 0x160
		ObjectRefHandle collisionIgnoredReference;															// 0x164
		REX::Float32 worldFOV;																				// 0x168
		REX::Float32 firstPersonFOV;																		// 0x16C
		REX::Float32 fovAdjustCurrent;																		// 0x170
		REX::Float32 fovAdjustTarget;																		// 0x174
		REX::Float32 fovAdjustPerSec;																		// 0x178
		REX::Float32 fovAnimatorAdjust;																		// 0x17C
		REX::Float32 collisionDistPercent;																	// 0x180
		REX::Float32 curPlayerVisible;																		// 0x184
		NiPoint3 bufferedCameraPos;																			// 0x188
		REX::Float32 heading;																				// 0x194
		REX::Float32 timeInPitchZero;																		// 0x198
		REX::Float32 originalPitchToZero;																	// 0x19C
		std::uint32_t furnitureCollisionGroup;																// 0x1A0
		bool allowAutoVanityMode;																			// 0x1A4
		bool bowZoomedIn;																					// 0x1A5
		bool freeRotationReady;																				// 0x1A6
		bool cameraPosBuffered;																				// 0x1A7
		bool zeroOutPitch;																					// 0x1A8
		bool adjustFOV;																						// 0x1A9
		bool trailerCameraMode;																				// 0x1AA
		bool pipboyMode;																					// 0x1AB
		bool savedFadeOutCloseActors;																		// 0x1AC
	};

	static_assert(sizeof(PlayerCamera) == 0x1B0);
}
