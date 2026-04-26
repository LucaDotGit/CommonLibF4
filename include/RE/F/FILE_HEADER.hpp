#pragma once

namespace RE
{
	class FILE_HEADER
	{
	public:
		// members
		REX::Float32 version;	  // 00
		std::uint32_t formCount;  // 04
		std::uint32_t nextFormID; // 08
	};
	static_assert(sizeof(FILE_HEADER) == 0x0C);
}
