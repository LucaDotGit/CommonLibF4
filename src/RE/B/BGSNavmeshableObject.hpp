#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class NavMesh;

	class BGSNavmeshableObject
	{
	public:
		inline static constexpr const auto& RTTI = RTTI::BGSNavmeshableObject;

		// members
		BSTSmartPointer<NavMesh> embeddedNavmesh; // 0x00
	};

	static_assert(sizeof(BGSNavmeshableObject) == 0x08);
}
