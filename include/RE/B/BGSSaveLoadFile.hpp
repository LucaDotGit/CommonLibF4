#pragma once

namespace RE
{
	class BSFile;

	class BGSSaveLoadFile
	{
	public:
		// members
		std::array<char, REX::W32::MAX_PATH> fileName; // 000
		BSFile* file;								   // 108
		std::int32_t simulatedFileSize;				   // 110
		std::int32_t simulatedFilePosition;			   // 114
	};
	static_assert(sizeof(BGSSaveLoadFile) == 0x118);
}
