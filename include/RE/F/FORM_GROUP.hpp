#pragma once

#include "RE/F/FORM.hpp"

namespace RE
{
	class FORM_GROUP
	{
	public:
		// members
		FORM data;						// 00
		std::uint64_t groupOffset{ 0 }; // 18
	};
	static_assert(sizeof(FORM_GROUP) == 0x20);
}
