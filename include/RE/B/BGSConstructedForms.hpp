#pragma once

#include "RE/B/BSTArray.hpp"

namespace RE
{
	class ConstructFormData;

	class BGSConstructedForms
	{
	public:
		// members
		std::array<BSTArray<ConstructFormData>, 3> formsArray; // 00
	};
	static_assert(sizeof(BGSConstructedForms) == 0x48);
}
