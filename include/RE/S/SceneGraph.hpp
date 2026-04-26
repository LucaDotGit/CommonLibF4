#pragma once

#include "RE/B/BSSceneGraph.hpp"

namespace RE
{
	class __declspec(novtable) SceneGraph
		: public BSSceneGraph // 000
	{
	public:
		inline static constexpr auto RTTI{ RTTI::SceneGraph };
		inline static constexpr auto VTABLE{ VTABLE::SceneGraph };
		inline static constexpr auto NI_RTTI{ Ni_RTTI::SceneGraph };

		// members
		REX::Float32 customNearDistance; // 160
		REX::Float32 customFarDistance;	 // 164
		bool customNearDistanceActive;	 // 168
		bool customFarDistanceActive;	 // 169
	};
	static_assert(sizeof(SceneGraph) == 0x170);
}
