#pragma once

namespace RE
{
	class AITimeStamp
	{
	public:
		// members
		REX::Float32 timeStamp; // 00
	};
	static_assert(sizeof(AITimeStamp) == 0x04);
}
