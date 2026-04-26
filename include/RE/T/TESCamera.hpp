#pragma once

#include "RE/B/BSTPoint.hpp"
#include "RE/B/BSTSmartPointer.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class NiNode;
	class TESCameraState;

	class __declspec(novtable) TESCamera
	{
	public:
		inline static constexpr auto RTTI{ RTTI::TESCamera };
		inline static constexpr auto VTABLE{ VTABLE::TESCamera };

		virtual ~TESCamera(); // 00

		// add
		virtual void SetCameraRoot(NiNode* a_cameraRoot);				 // 01
		virtual void SetEnabled(bool a_enabled) { enabled = a_enabled; } // 02
		virtual void Update();											 // 03

		// members
		BSTPoint2<REX::Float32> rotationInput;		  // 08
		BSTPoint3<REX::Float32> translationInput;	  // 10
		REX::Float32 zoomInput;						  // 1C
		NiPointer<NiNode> cameraRoot;				  // 20
		BSTSmartPointer<TESCameraState> currentState; // 28
		bool enabled;								  // 30
	};
	static_assert(sizeof(TESCamera) == 0x38);
}
