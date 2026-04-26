#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/N/NiPoint.hpp"

namespace RE
{
	class NiObject;

	class NiCloningProcess
	{
	public:
		enum class CopyType : std::int32_t
		{
			kNone = 0,
			kCopyExact = 1,
			kCopyUnique = 2
		};

		// members
		BSTHashMap<NiObject*, NiObject*> cloneMap;	// 00
		BSTHashMap<NiObject*, bool> processMap;		// 30
		REX::Enum<CopyType, std::int32_t> copyType; // 60
		char appendChar;							// 64
		NiPoint3 scale;								// 68
	};
	static_assert(sizeof(NiCloningProcess) == 0x78);
}
