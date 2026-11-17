#pragma once

#include "RE/B/BSSceneGraph.hpp"

namespace RE
{
	class __declspec(novtable) SceneGraph : public BSSceneGraph // 0x000
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::SceneGraph;
		inline static constexpr const auto& VTABLE = VTABLE::SceneGraph;
		inline static constexpr const auto& NI_RTTI = Ni_RTTI::SceneGraph;

		// members
		REX::Float32 customNearDistance; // 0x160
		REX::Float32 customFarDistance;	 // 0x164
		bool customNearDistanceActive;	 // 0x168
		bool customFarDistanceActive;	 // 0x169
	};

#if (COMMONLIB_RUNTIME_VR == 0)
	static_assert(sizeof(SceneGraph) == 0x170);
#else
	static_assert(sizeof(SceneGraph) == 0x150);
#endif
}
