#pragma once

#include "RE/B/BSSimpleList.hpp"
#include "RE/C/CameraStates.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/T/ThirdPersonState.hpp"

namespace RE
{
	class __declspec(novtable) DialogueCameraState
		: public ThirdPersonState // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::DialogueCameraState };
		inline static constexpr auto VTABLE{ VTABLE::DialogueCameraState };
		inline static constexpr auto CAMERA_STATE{ CameraStates::kDialogue };

		enum class CameraAction : std::int32_t; // TODO
		enum class CameraZoom : std::int32_t;	// TODO

		~DialogueCameraState() override; // 00

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04
		void OnMouseMoveEvent(const MouseMoveEvent* a_event) override;	 // 06
		void OnButtonEvent(const ButtonEvent* a_event) override;		 // 08

		// override (TESCameraState)
		void Begin() override;												// 09
		void End() override;												// 0A
		void Update(BSTSmartPointer<TESCameraState>& a_nextState) override; // 0B
		void GetRotation(NiQuaternion& a_rotation) const override;			// 0C
		void GetTranslation(NiPoint3& a_translation) const override;		// 0D
		void SaveGame(BGSSaveFormBuffer* a_saveGameBuffer) override;		// 0E
		void LoadGame(BGSLoadFormBuffer* a_loadGameBuffer) override;		// 0F
		void Revert(BGSLoadFormBuffer* a_loadGameBuffer) override;			// 10

		// members
		REX::Float32 cameraTimer;									   // 138
		REX::Float32 cameraMinTimer;								   // 13C
		BSSimpleList<BGSCameraShot>* cameraList;					   // 140
		BGSCameraShot* camera;										   // 148
		std::array<BGSCameraShot*, 4> lastCameras;					   // 150
		TESImageSpaceModifier* imageSpaceMod;						   // 170
		NiPointer<Actor> dialoguePlayer;							   // 178
		NiPointer<TESObjectREFR> dialogueTarget;					   // 180
		NiPointer<TESObjectREFR> dialogueSpeaker;					   // 188
		NiPointer<TESObjectREFR> dialogueListener;					   // 190
		NiPointer<TESObjectREFR> dialoguePrimary;					   // 198
		NiPointer<TESObjectREFR> dialogueEventCameraRef;			   // 1A0
		NiPointer<TESObjectREFR> dialogueEventCameraTargetRef;		   // 1A8
		NiPointer<TESObjectREFR> dialogueMidLookAt;					   // 1B0
		NiPointer<TESObjectREFR> dialogueMidGround;					   // 1B8
		REX::Float32 playbackTimer;									   // 1C0
		REX::Float32 nextSceneTimer;								   // 1C4
		BGSCameraPath* cameraPath;									   // 1C8
		REX::Enum<CameraAction, std::int32_t> dialogueCameraAction;	   // 1D0
		REX::Enum<CameraAction, std::int32_t> dialogueNewCameraAction; // 1D4
		REX::Float32 dialoguePathMaxTime;							   // 1D8
		BGSCameraPath* forceCameraPath;								   // 1E0
		REX::Enum<CameraZoom, std::int32_t> cameraZoom;				   // 1E8
		std::uint32_t shootActionsAvailable;						   // 1EC
		std::uint32_t shootActionsPlayed;							   // 1F0
		NiPoint3 cameraRotation;									   // 1F4
		NiPoint3 cameraTranslation;									   // 200
		NiPoint3 cameraStartingPosition;							   // 20C
		bool playerControlsReenabled;								   // 218
		bool playerOpening;											   // 219
		bool changeSpeakerAndListener;								   // 21A
		bool enteredFromFirstPerson;								   // 21B
		bool allowFirstPerson;										   // 21C
		bool playingEventCamera;									   // 21D
	};
	static_assert(sizeof(DialogueCameraState) == 0x220);
}
