#pragma once

#include "RE/N/NiNode.hpp"
#include "RE/N/NiPointer.hpp"

namespace RE
{
	class BSCullingProcess;
	class NiCamera;
	class NiVisibleArray;

	class __declspec(novtable) BSSceneGraph : public NiNode // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BSSceneGraph;
		inline static constexpr const auto& VTABLE = VTABLE::BSSceneGraph;

		~BSSceneGraph() override; // 0x00

		// add
		virtual auto GetFarDistance() const -> REX::Float32;					// 0x43
		virtual auto GetNearDistance() const -> REX::Float32;					// 0x44
		virtual void SetViewDistanceBasedOnFrameRate(REX::Float32 a_frameRate); // 0x45

		// members
		NiPointer<NiCamera> camera; // 0x140
		NiVisibleArray* visArray;	// 0x148
		BSCullingProcess* culler;	// 0x150
		bool menuSceneGraph;		// 0x158
		REX::Float32 currentFOV;	// 0x15C
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(BSSceneGraph) == 0x160);
#else
	static_assert(sizeof(BSSceneGraph) == 0x140);
#endif
}
