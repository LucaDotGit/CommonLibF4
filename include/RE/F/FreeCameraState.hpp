#pragma once

#include "RE/B/BSTPoint.hpp"
#include "RE/N/NiPoint.hpp"
#include "RE/T/TESCameraState.hpp"

namespace RE
{
	class __declspec(novtable) FreeCameraState
		: public TESCameraState // 00
	{
	public:
		inline static constexpr auto RTTI{ RTTI::FreeCameraState };
		inline static constexpr auto VTABLE{ VTABLE::FreeCameraState };
		inline static constexpr auto CAMERA_STATE{ CameraStates::kFree };

		~FreeCameraState() override; // 00

		// override (BSInputEventUser)
		bool ShouldHandleEvent(const InputEvent* a_event) override;		 // 01
		void OnThumbstickEvent(const ThumbstickEvent* a_event) override; // 04
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
		NiPoint3 translation;					 // 28
		BSTPoint2<REX::Float32> rotation;		 // 34
		BSTPoint2<REX::Float32> upDown;			 // 3C
		BSTPoint2<REX::Float32> leftThumbstick;	 // 44
		BSTPoint2<REX::Float32> rightThumbstick; // 4C
		std::int16_t worldZDirection;			 // 54
		bool runInput;							 // 56
		bool lockToZPlane;						 // 57
	};
	static_assert(sizeof(FreeCameraState) == 0x58);
}
