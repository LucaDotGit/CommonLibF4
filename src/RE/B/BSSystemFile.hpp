#pragma once

namespace RE
{
	class BSSystemFile
	{
	public:
		class Info
		{
		public:
			// members
			REX::W32::FILETIME accessTime; // 0x00
			REX::W32::FILETIME modifyTime; // 0x08
			REX::W32::FILETIME createTime; // 0x10
			std::size_t fileSize{0};	   // 0x18
		};

		static_assert(sizeof(Info) == 0x20);

		// members
		std::uint32_t flags{0};	   // 0x00 - To-Do
		void* fileHandle{nullptr}; // 0x08
	};

	static_assert(sizeof(BSSystemFile) == 0x10);
}
