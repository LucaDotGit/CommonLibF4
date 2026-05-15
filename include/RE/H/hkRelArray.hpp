#pragma once

namespace RE
{
	template <class T>
	class hkRelArray
	{
	public:
		// members
		std::uint16_t size;	  // 00
		std::uint16_t offset; // 02
	};
	static_assert(sizeof(hkRelArray<std::int32_t>) == 0x04);
}
