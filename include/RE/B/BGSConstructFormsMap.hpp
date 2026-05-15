#pragma once

#include "RE/B/BSTHashMap.hpp"
#include "RE/C/ConstructFormData.hpp"

namespace RE
{
	class BGSConstructFormsMap
		: public BSTHashMap<std::uint32_t, ConstructFormData> // 00
	{
	public:
		// members
		std::uint32_t iFlags; // 30
	};
	static_assert(sizeof(BGSConstructFormsMap) == 0x38);
}
