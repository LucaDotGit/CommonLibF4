#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint3.hpp"

namespace RE
{
	class NiObject;

	class NiCloningProcess
	{
	public:
		enum class CopyType : std::int32_t
		{
			None = 0,
			CopyExact = 1,
			CopyUnique = 2
		};

		// members
		BSTHashMap<NiObject*, NiObject*> cloneMap;	// 0x00
		BSTHashMap<NiObject*, bool> processMap;		// 0x30
		REX::Enum<CopyType, std::int32_t> copyType; // 0x60
		char appendChar;							// 0x64
		NiPoint3 scale;								// 0x68
	};

	static_assert(sizeof(NiCloningProcess) == 0x78);
}
