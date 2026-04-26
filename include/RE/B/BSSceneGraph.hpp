#pragma once

#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSCullingProcess;
	class NiCamera;
	class NiVisibleArray;

	class __declspec(novtable) BSSceneGraph
		: public NiNode // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BSSceneGraph };
		inline static constexpr auto VTABLE{ VTABLE::BSSceneGraph };

		// add
		virtual REX::Float32 GetFarDistance() const;							// 43
		virtual REX::Float32 GetNearDistance() const;							// 44
		virtual void SetViewDistanceBasedOnFrameRate(REX::Float32 a_frameRate); // 45

		// members
		NiPointer<NiCamera> camera; // 140
		NiVisibleArray* visArray;	// 148
		BSCullingProcess* culler;	// 150
		bool menuSceneGraph;		// 158
		REX::Float32 currentFOV;	// 15C
	};
	static_assert(sizeof(BSSceneGraph) == 0x160);
}
