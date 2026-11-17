#pragma once

#include "RE/B/BSTPoint2.hpp"
#include "RE/B/BSTPoint3.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiNode;
	class TESCameraState;

	class __declspec(novtable) TESCamera
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::TESCamera;
		inline static constexpr const auto& VTABLE = VTABLE::TESCamera;

		virtual ~TESCamera(); // 0x00

		// add
		virtual void SetCameraRoot(NiNode* a_cameraRoot); // 0x01

		virtual void SetEnabled(bool a_enabled) // 0x02
		{
			enabled = a_enabled;
		}

		virtual void Update(); // 0x03

		// members
		BSTPoint2F rotationInput;					  // 0x08
		BSTPoint3F translationInput;				  // 0x10
		REX::Float32 zoomInput;						  // 0x1C
		NiPointer<NiNode> cameraRoot;				  // 0x20
		BSTSmartPointer<TESCameraState> currentState; // 0x28
		bool enabled;								  // 0x30
	};

	static_assert(sizeof(TESCamera) == 0x38);
}
