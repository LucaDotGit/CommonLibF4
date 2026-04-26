#pragma once

namespace RE
{
	class BSEventFlag
	{
	public:
		// members
		void* event{ nullptr }; // 00
	};
	static_assert(sizeof(BSEventFlag) == 0x08);
}
