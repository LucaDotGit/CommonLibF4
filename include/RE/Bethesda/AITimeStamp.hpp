#pragma once

namespace RE
{
	class AITimeStamp
	{
	public:
		// members
		float timeStamp; // 00
	};
	static_assert(sizeof(AITimeStamp) == 0x4);
}
