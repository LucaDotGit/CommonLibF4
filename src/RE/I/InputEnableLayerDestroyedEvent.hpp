#pragma once

namespace RE
{
	class InputEnableLayerDestroyedEvent
	{
	public:
		// members
		std::uint32_t layerID; // 0x00
	};

	static_assert(sizeof(InputEnableLayerDestroyedEvent) == 0x04);
}
