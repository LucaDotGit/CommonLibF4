#pragma once

namespace RE
{
	class hkStringPtr
	{
	public:
		// members
		const char* stringAndFlags{nullptr}; // 0x00
	};

	static_assert(sizeof(hkStringPtr) == 0x08);
}
