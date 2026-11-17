#pragma once

#include "RE/B/BSTPoint2.hpp"
#include "RE/N/NiPoint3.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class __declspec(novtable) FreeCameraState : public TESCameraState // 0x00
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::FreeCameraState;
		inline static constexpr const auto& VTABLE = VTABLE::FreeCameraState;
		inline static constexpr auto CAMERA_STATE = CameraStates::Free;

		~FreeCameraState() override; // 0x00

		// override (BSInputEventUser)
		auto ShouldHandleEvent(const InputEvent* a_event) -> bool override; // 0x01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override;	// 0x04
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
		NiPoint3 translation;		  // 0x28
		BSTPoint2F rotation;		  // 0x34
		BSTPoint2F upDown;			  // 0x3C
		BSTPoint2F leftThumbstick;	  // 0x44
		BSTPoint2F rightThumbstick;	  // 0x4C
		std::int16_t worldZDirection; // 0x54
		bool runInput;				  // 0x56
		bool lockToZPlane;			  // 0x57
	};

	static_assert(sizeof(FreeCameraState) == 0x58);
}
