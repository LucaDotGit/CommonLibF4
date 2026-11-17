#pragma once

#include "RE/B/BSFixedString.hpp"
#include "RE/N/NiPoint2.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/N/NiPointer.hpp"
#include "RE/N/NiQuaternion.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class NiAVObject;
	class NiNode;

	class __declspec(novtable) ThirdPersonState : public TESCameraState // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::ThirdPersonState;
		inline static constexpr const auto& VTABLE = VTABLE::ThirdPersonState;
		inline static constexpr auto CAMERA_STATE = CameraStates::ThirdPerson;

		~ThirdPersonState() override; // 0x00

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

		// add
		virtual void ProcessWeaponDrawnChange(bool a_drawn);						  // 0x11
		virtual auto GetFreeRotationMode() const -> bool;							  // 0x12
		virtual void SetFreeRotationMode(bool a_cameraEnable, bool a_modifyRotation); // 0x13
		virtual void UpdateRotation();												  // 0x14
		virtual void HandleLookInput(const NiPoint2& a_input);						  // 0x15

		// members
		NiQuaternion rotation;				  // 0x028
		NiQuaternion animationRotation;		  // 0x038
		NiPoint3 translation;				  // 0x048
		NiPoint3 preCollisionTranslation;	  // 0x054
		NiPoint3 targetShoulderOffset;		  // 0x060
		NiPoint3 currentShoulderOffset;		  // 0x06C
		NiPoint3 animationTranslation;		  // 0x078
		NiPoint3 lastTranslation;			  // 0x084
		NiPoint3 rootOffset;				  // 0x090
		NiPoint3 sideOffsetCollisionBlend;	  // 0x09C
		NiPoint3 nearestHit;				  // 0x0A8
		NiPoint3 nearestHitDir;				  // 0x0B4
		NiPoint2 freeRotation;				  // 0x0C0
		BSFixedString animatedBoneName;		  // 0x0C8
		NiAVObject* thirdPersonCameraObj;	  // 0x0D0
		NiNode* thirdPersonFOVControl;		  // 0x0D8
		NiPointer<NiAVObject> animatedBone;	  // 0x0E0
		REX::Float32 targetZoomOffset;		  // 0x0E8
		REX::Float32 currentZoomOffset;		  // 0x0EC
		REX::Float32 targetYaw;				  // 0x0F0
		REX::Float32 currentYaw;			  // 0x0F4
		REX::Float32 cameraHeightAdjust;	  // 0x0F8
		REX::Float32 savedZoomOffset;		  // 0x0FC
		REX::Float32 pitchZoomOffset;		  // 0x100
		REX::Float32 zoomChange;			  // 0x104
		NiPoint2 startTogglePOVFreeRot;		  // 0x108
		REX::Float32 collisionRecoveryFactor; // 0x110
		REX::Float32 savedCollisionPercent;	  // 0x114
		REX::Float32 animationBlend;		  // 0x118
		REX::Float32 animationBlendDirection; // 0x11C
		REX::Float32 searchDistanceBlend;	  // 0x120
		REX::Float32 searchLastCameraYaw;	  // 0x124
		bool freeRotationEnabled;			  // 0x128
		bool zoomingInto1st;				  // 0x129
		bool show3rdPersonModel;			  // 0x12A
		bool preserveRotation;				  // 0x12B
		bool animatorMode;					  // 0x12C
		bool applyOffsets;					  // 0x12D
		bool togglePOVPressRegistered;		  // 0x12E
		bool wasUsingScreenSpaceLastFrame;	  // 0x12F
		bool ironSights;					  // 0x130
	};

	static_assert(sizeof(ThirdPersonState) == 0x138);
}
