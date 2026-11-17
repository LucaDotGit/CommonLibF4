#pragma once

namespace RE::BSResource
{
	class Info
	{
	public:
		// members
		REX::W32::FILETIME modifyTime; // 0x00
		REX::W32::FILETIME createTime; // 0x08
		std::uint64_t fileSize;		   // 0x10
	};

	static_assert(sizeof(Info) == 0x18);
}
