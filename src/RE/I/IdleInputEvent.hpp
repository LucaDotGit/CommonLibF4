#pragma once

namespace RE
{
	class IdleInputEvent
	{
	public:
		// members
		bool starting; // 0x00
	};

	static_assert(sizeof(IdleInputEvent) == 0x01);
}
