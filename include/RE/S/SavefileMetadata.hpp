#pragma once

#include "RE/B/BSStringT.hpp"

namespace RE
{
	class SavefileMetadata
	{
	public:
		void FillDataFromFileName(const char* a_saveName)
		{
			using FuncType = decltype(&SavefileMetadata::FillDataFromFileName);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::SavefileMetadata::FillDataFromFileName };
			FUNC(this, a_saveName);
		}

		// members
		std::array<char, REX::W32::MAX_PATH> fileName; // 00
		REX::W32::FILETIME creationTimeStamp;		   // 104
		std::uint64_t playerLevel;					   // 110
		std::uint32_t filenameVersion;				   // 118
		std::uint32_t saveGameNumber;				   // 11C
		std::uint64_t playerID;						   // 120
		BSString playerName;						   // 128
		BSString playerLocID;						   // 138
		BSString playTime;							   // 148
		bool isValid;								   // 158
		bool hasSaveNumber;							   // 159
		bool needsSync;								   // 15A
		bool modded;								   // 15B
		bool survival;								   // 15C
	};
	static_assert(sizeof(SavefileMetadata) == 0x160);
}
