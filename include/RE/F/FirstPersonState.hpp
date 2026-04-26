#pragma once

#include "RE/C/CameraStates.hpp"
#include "RE/N/NiAVObject.hpp"
#include "RE/N/NiNode.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class __declspec(novtable) FirstPersonState
		: public TESCameraState // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FirstPersonState };
		inline static constexpr auto VTABLE{ VTABLE::FirstPersonState };
		inline static constexpr auto CAMERA_STATE{ CameraStates::kFirstPerson };

		~FirstPersonState() override; // 00

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override; // 01
		void OnButtonEvent(const ButtonEvent* a_event) override;	// 08

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
		NiPoint3 lastPosition;				  // 28
		NiPoint3 lastFrameSpringVelocity;	  // 34
		NiPoint3 dampingOffset;				  // 40
		NiAVObject* firstPersonCameraObject;  // 50
		NiNode* firstPersonPOVControl;		  // 58
		REX::Float32 sittingRotation;		  // 60
		REX::Float32 sittingPitch;			  // 64
		REX::Float32 currentPitchOffsetMult;  // 68
		REX::Float32 previousPitchOffsetMult; // 6C
		REX::Float32 currentPitchOffset;	  // 70
		REX::Float32 targetPitchOffset;		  // 74
		REX::Float32 ironSightsAnim;		  // 78
		REX::Float32 dampeningWeight;		  // 7C
		bool cameraOverride;				  // 80
		bool cameraPitchOverride;			  // 81
		bool isOffsettingPitch;				  // 82
		bool togglePOVPressRegistered;		  // 83
		bool previouslyInIronSights;		  // 84
	};
	static_assert(sizeof(FirstPersonState) == 0x88);
}
