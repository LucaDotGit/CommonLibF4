#pragma once

namespace RE
{
	class CLASS_DATA
	{
	public:
		// members
		std::uint32_t serviceFlags;	  // 0x00
		REX::Float32 bleedoutDefault; // 0x04
	};

	static_assert(sizeof(CLASS_DATA) == 0x08);
}
