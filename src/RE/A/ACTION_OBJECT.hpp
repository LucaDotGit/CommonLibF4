#pragma once

namespace RE
{
	class ACTION_OBJECT
	{
	public:
		// members
		TESForm* form;		 // 0x00
		std::uint32_t flags; // 0x08
	};

	static_assert(sizeof(ACTION_OBJECT) == 0x10);
}
