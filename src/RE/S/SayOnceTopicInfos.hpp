#pragma once

namespace RE
{
	class SayOnceTopicInfos
	{
	public:
		// members
		TESTopicInfo* info;		// 0x00
		std::int32_t dateStamp; // 0x08
		REX::Float32 hourStamp; // 0x0C
	};

	static_assert(sizeof(SayOnceTopicInfos) == 0x10);
}
