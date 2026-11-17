#pragma once

namespace RE
{
	class UnequipObjectFunctor
	{
	public:
		// members
		Actor* actor; // 0x00
	};

	static_assert(sizeof(UnequipObjectFunctor) == 0x08);
}
