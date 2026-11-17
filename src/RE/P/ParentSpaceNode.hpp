#pragma once

namespace RE
{
	class ParentSpaceNode
	{
	public:
		// members
		bool worldspace;			 // 0x00
		TESWorldSpace* worldSpace;	 // 0x08
		TESObjectCELL* interiorCell; // 0x10
	};

	static_assert(sizeof(ParentSpaceNode) == 0x18);
}
