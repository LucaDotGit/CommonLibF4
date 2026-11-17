#pragma once

#include "RE/B/BSString.hpp"

namespace RE
{
	class SavefileMetadata
	{
	public:
		void FillDataFromFileName(const char* a_saveName)
		{
			using FuncType = decltype(&SavefileMetadata::FillDataFromFileName);
			static const auto FUNC = REL::Relocation<FuncType>(ID::SavefileMetadata::FillDataFromFileName);
			std::invoke(FUNC, this, a_saveName);
		}

		// members
		REX::StaticString<REX::W32::MAX_PATH> fileName; // 0x00
		REX::W32::FILETIME creationTimeStamp;			// 0x104
		std::uint64_t playerLevel;						// 0x110
		std::uint32_t filenameVersion;					// 0x118
		std::uint32_t saveGameNumber;					// 0x11C
		std::uint64_t playerID;							// 0x120
		BSString playerName;							// 0x128
		BSString playerLocID;							// 0x138
		BSString playTime;								// 0x148
		bool isValid;									// 0x158
		bool hasSaveNumber;								// 0x159
		bool needsSync;									// 0x15A
		bool modded;									// 0x15B
		bool survival;									// 0x15C
	};

	static_assert(sizeof(SavefileMetadata) == 0x160);
}
