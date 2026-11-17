#pragma once

namespace RE
{
	class SCRIPT_HEADER
	{
	public:
		// members
		std::uint32_t variableCount;  // 0x00
		std::uint32_t refObjectCount; // 0x04
		std::uint32_t dataSize;		  // 0x08
		std::uint32_t lastID;		  // 0x0C
		bool isQuestScript;			  // 0x10
		bool isMagicEffectScript;	  // 0x11
		bool isCompiled;			  // 0x12
	};

	static_assert(sizeof(SCRIPT_HEADER) == 0x14);
}
