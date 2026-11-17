#pragma once

namespace RE
{
	class UniqueNPCData
	{
	public:
		// members
		TESNPC* npc;			// 0x00
		TESFormID refID;		// 0x08
		BGSLocation* editorLoc; // 0x10
	};

	static_assert(sizeof(UniqueNPCData) == 0x18);
}
