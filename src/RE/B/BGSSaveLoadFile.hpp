#pragma once

namespace RE
{
	class BSFile;

	class BGSSaveLoadFile
	{
	public:
		// members
		REX::StaticString<REX::W32::MAX_PATH> fileName; // 0x000
		BSFile* file;									// 0x108
		std::int32_t simulatedFileSize;					// 0x110
		std::int32_t simulatedFilePosition;				// 0x114
	};

	static_assert(sizeof(BGSSaveLoadFile) == 0x118);
}
