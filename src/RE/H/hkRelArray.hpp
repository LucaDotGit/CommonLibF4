#pragma once

namespace RE
{
	template <class T>
	class hkRelArray
	{
	public:
		// members
		std::uint16_t size;	  // 0x00
		std::uint16_t offset; // 0x02
	};

	static_assert(sizeof(hkRelArray<std::int32_t>) == 0x04);
}
