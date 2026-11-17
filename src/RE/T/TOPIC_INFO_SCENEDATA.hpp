#pragma once

namespace RE
{
	class TOPIC_INFO_SCENEDATA
	{
	public:
		// members
		BGSScene* scene;	 // 0x00
		std::uint32_t phase; // 0x08
	};

	static_assert(sizeof(TOPIC_INFO_SCENEDATA) == 0x10);
}
