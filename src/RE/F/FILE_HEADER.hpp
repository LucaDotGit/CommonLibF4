#pragma once

namespace RE
{
	class FILE_HEADER
	{
	public:
		// members
		REX::Float32 version;	  // 0x00
		std::uint32_t formCount;  // 0x04
		std::uint32_t nextFormID; // 0x08
	};

	static_assert(sizeof(FILE_HEADER) == 0x0C);
}
