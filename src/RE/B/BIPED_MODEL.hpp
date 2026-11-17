#pragma once

namespace RE
{
	class BIPED_MODEL
	{
	public:
		// members
		std::uint32_t bipedObjectSlots; // 0x00
	};

	static_assert(sizeof(BIPED_MODEL) == 0x04);
}
