#pragma once

#include "RE/F/FORM.hpp"

namespace RE
{
	class FORM_GROUP
	{
	public:
		// members
		FORM data;					  // 0x00
		std::uint64_t groupOffset{0}; // 0x18
	};

	static_assert(sizeof(FORM_GROUP) == 0x20);
}
