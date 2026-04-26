#pragma once

#include "RE/B/BSTSmartPointer.hpp"

namespace RE
{
	class NavMesh;

	class BGSNavmeshableObject
	{
	public:
		inline static constexpr auto RTTI{ RTTI::BGSNavmeshableObject };

		// members
		BSTSmartPointer<NavMesh> embeddedNavmesh; // 00
	};
	static_assert(sizeof(BGSNavmeshableObject) == 0x08);
}
