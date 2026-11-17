#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/C/CameraStates.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/ThirdPersonState.hpp"

namespace RE
{
	class __declspec(novtable) DialogueCameraState : public ThirdPersonState // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::DialogueCameraState;
		inline static constexpr const auto& VTABLE = VTABLE::DialogueCameraState;
		inline static constexpr auto CAMERA_STATE = CameraStates::Dialogue;

		enum class CameraAction : std::int32_t; // To-Do
		enum class CameraZoom : std::int32_t;	// To-Do

		~DialogueCameraState() override; // 0x00

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
		void OnMouseMoveEvent(const MouseMoveEvent* a_event) override;		// 0x06
		void OnButtonEvent(const ButtonEvent* a_event) override;			// 0x08

		// override (TESCameraState)
		void Begin() override;												// 0x09
		void End() override;												// 0x0A
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override; // 0x0B
		void GetRotation(NiQuaternion& a_rotation) const override;			// 0x0C
		void GetTranslation(NiPoint3& a_translation) const override;		// 0x0D
		void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) override;		// 0x0E
		void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer) override;		// 0x0F
		void Revert(BGSLoadFormBuffer* a_loadGameBuffer) override;			// 0x10

		// members
		REX::Float32 cameraTimer;									   // 0x138
		REX::Float32 cameraMinTimer;								   // 0x13C
		BSSimpleList<BGSCameraShot>* cameraList;					   // 0x140
		BGSCameraShot* cameraShot;									   // 0x148
		std::array<BGSCameraShot*, 4> lastCameras;					   // 0x150
		TESImageSpaceModifier* imageSpaceMod;						   // 0x170
		NiPointer<Actor> dialoguePlayer;							   // 0x178
		NiPointer<TESObjectREFR> dialogueTarget;					   // 0x180
		NiPointer<TESObjectREFR> dialogueSpeaker;					   // 0x188
		NiPointer<TESObjectREFR> dialogueListener;					   // 0x190
		NiPointer<TESObjectREFR> dialoguePrimary;					   // 0x198
		NiPointer<TESObjectREFR> dialogueEventCameraRef;			   // 0x1A0
		NiPointer<TESObjectREFR> dialogueEventCameraTargetRef;		   // 0x1A8
		NiPointer<TESObjectREFR> dialogueMidLookAt;					   // 0x1B0
		NiPointer<TESObjectREFR> dialogueMidGround;					   // 0x1B8
		REX::Float32 playbackTimer;									   // 0x1C0
		REX::Float32 nextSceneTimer;								   // 0x1C4
		BGSCameraPath* cameraPath;									   // 0x1C8
		REX::Enum<CameraAction, std::int32_t> dialogueCameraAction;	   // 0x1D0
		REX::Enum<CameraAction, std::int32_t> dialogueNewCameraAction; // 0x1D4
		REX::Float32 dialoguePathMaxTime;							   // 0x1D8
		BGSCameraPath* forceCameraPath;								   // 0x1E0
		REX::Enum<CameraZoom, std::int32_t> cameraZoom;				   // 0x1E8
		std::uint32_t shootActionsAvailable;						   // 0x1EC
		std::uint32_t shootActionsPlayed;							   // 0x1F0
		NiPoint3 cameraRotation;									   // 0x1F4
		NiPoint3 cameraTranslation;									   // 0x200
		NiPoint3 cameraStartingPosition;							   // 0x20C
		bool playerControlsReenabled;								   // 0x218
		bool playerOpening;											   // 0x219
		bool changeSpeakerAndListener;								   // 0x21A
		bool enteredFromFirstPerson;								   // 0x21B
		bool allowFirstPerson;										   // 0x21C
		bool playingEventCamera;									   // 0x21D
	};

	static_assert(sizeof(DialogueCameraState) == 0x220);
}
