#pragma once

namespace RE
{
	class UniqueNPCData
	{
	public:
		// members
		TESNPC* npc;			// 00
		TESFormID refID;		// 08
		BGSLocation* editorLoc; // 10
	};
	static_assert(sizeof(UniqueNPCData) == 0x18);
}
