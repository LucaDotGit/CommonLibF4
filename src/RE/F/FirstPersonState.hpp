#pragma once

#include "RE/C/CameraStates.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class __declspec(novtable) FirstPersonState : public TESCameraState // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FirstPersonState;
		inline static constexpr const auto& VTABLE = VTABLE::FirstPersonState;
		inline static constexpr auto CAMERA_STATE = CameraStates::FirstPerson;

		~FirstPersonState() override; // 0x00

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
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
		NiPoint3 lastPosition;				  // 0x28
		NiPoint3 lastFrameSpringVelocity;	  // 0x34
		NiPoint3 dampingOffset;				  // 0x40
		NiAVObject* firstPersonCameraObject;  // 0x50
		NiNode* firstPersonPOVControl;		  // 0x58
		REX::Float32 sittingRotation;		  // 0x60
		REX::Float32 sittingPitch;			  // 0x64
		REX::Float32 currentPitchOffsetMult;  // 0x68
		REX::Float32 previousPitchOffsetMult; // 0x6C
		REX::Float32 currentPitchOffset;	  // 0x70
		REX::Float32 targetPitchOffset;		  // 0x74
		REX::Float32 ironSightsAnim;		  // 0x78
		REX::Float32 dampeningWeight;		  // 0x7C
		bool cameraOverride;				  // 0x80
		bool cameraPitchOverride;			  // 0x81
		bool isOffsettingPitch;				  // 0x82
		bool togglePOVPressRegistered;		  // 0x83
		bool previouslyInIronSights;		  // 0x84
	};

	static_assert(sizeof(FirstPersonState) == 0x88);
}
