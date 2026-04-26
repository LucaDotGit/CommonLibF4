#pragma once

namespace Scaleform
{
	class LogMessageId
	{
	public:
		// members
		std::int32_t id; // 00
	};
	static_assert(sizeof(LogMessageId) == 0x04);
}
