#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiQuaternion.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class NiAVObject;
	class NiNode;

	class __declspec(novtable) ThirdPersonState
		: public TESCameraState // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::ThirdPersonState };
		inline static constexpr auto VTABLE{ VTABLE::ThirdPersonState };
		inline static constexpr auto CAMERA_STATE{ CameraStates::kThirdPerson };

		~ThirdPersonState() override; // 00

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

		// add
		virtual void ProcessWeaponDrawnChange(bool a_drawn);						  // 11
		virtual bool GetFreeRotationMode() const;									  // 12
		virtual void SetFreeRotationMode(bool a_cameraEnable, bool a_modifyRotation); // 13
		virtual void UpdateRotation();												  // 14
		virtual void HandleLookInput(const NiPoint2& a_input);						  // 15

		// members
		NiQuaternion rotation;				  // 028
		NiQuaternion animationRotation;		  // 038
		NiPoint3 translation;				  // 048
		NiPoint3 preCollisionTranslation;	  // 054
		NiPoint3 targetShoulderOffset;		  // 060
		NiPoint3 currentShoulderOffset;		  // 06C
		NiPoint3 animationTranslation;		  // 078
		NiPoint3 lastTranslation;			  // 084
		NiPoint3 rootOffset;				  // 090
		NiPoint3 sideOffsetCollisionBlend;	  // 09C
		NiPoint3 nearestHit;				  // 0A8
		NiPoint3 nearestHitDir;				  // 0B4
		NiPoint2 freeRotation;				  // 0C0
		BSFixedString animatedBoneName;		  // 0C8
		NiAVObject* thirdPersonCameraObj;	  // 0D0
		NiNode* thirdPersonFOVControl;		  // 0D8
		NiPointer<NiAVObject> animatedBone;	  // 0E0
		REX::Float32 targetZoomOffset;		  // 0E8
		REX::Float32 currentZoomOffset;		  // 0EC
		REX::Float32 targetYaw;				  // 0F0
		REX::Float32 currentYaw;			  // 0F4
		REX::Float32 cameraHeightAdjust;	  // 0F8
		REX::Float32 savedZoomOffset;		  // 0FC
		REX::Float32 pitchZoomOffset;		  // 100
		REX::Float32 zoomChange;			  // 104
		NiPoint2 startTogglePOVFreeRot;		  // 108
		REX::Float32 collisionRecoveryFactor; // 110
		REX::Float32 savedCollisionPercent;	  // 114
		REX::Float32 animationBlend;		  // 118
		REX::Float32 animationBlendDirection; // 11C
		REX::Float32 searchDistanceBlend;	  // 120
		REX::Float32 searchLastCameraYaw;	  // 124
		bool freeRotationEnabled;			  // 128
		bool zoomingInto1st;				  // 129
		bool show3rdPersonModel;			  // 12A
		bool preserveRotation;				  // 12B
		bool animatorMode;					  // 12C
		bool applyOffsets;					  // 12D
		bool togglePOVPressRegistered;		  // 12E
		bool wasUsingScreenSpaceLastFrame;	  // 12F
		bool ironSights;					  // 130
	};
	static_assert(sizeof(ThirdPersonState) == 0x138);
}
