#pragma once

namespace RE
{
	class SayOnceTopicInfos
	{
	public:
		// members
		TESTopicInfo* info;		// 00
		std::int32_t dateStamp; // 08
		REX::Float32 hourStamp; // 0C
	};
	static_assert(sizeof(SayOnceTopicInfos) == 0x10);
}
