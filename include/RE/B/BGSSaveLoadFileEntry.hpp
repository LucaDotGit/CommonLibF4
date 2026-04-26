#pragma once

namespace RE
{
	class BGSSaveLoadFileEntry
	{
	public:
		void DeleteGame()
		{
			using FuncType = decltype(&BGSSaveLoadFileEntry::DeleteGame);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadFileEntry::DeleteGame };
			FUNC(this);
		}

		void LoadData()
		{
			using FuncType = decltype(&BGSSaveLoadFileEntry::LoadData);
			static const auto FUNC = REL::Relocation<FuncType>{ ID::BGSSaveLoadFileEntry::LoadData };
			FUNC(this);
		}

		// members
		char* fileName;					// 00
		char* playerName;				// 08
		char* playerTitle;				// 10
		char* location;					// 18
		char* playTime;					// 20
		char* raceName;					// 28
		std::int32_t version;			// 30
		std::uint32_t saveGameNumber;	// 34
		std::int32_t playerLevel;		// 38
		REX::Float32 levelProgress;		// 3C
		REX::Float32 levelThreshold;	// 40
		std::int32_t screenshotWidth;	// 44
		std::int32_t screenshotHeight;	// 48
		std::int32_t screenshotOffsetX; // 4C
		REX::W32::FILETIME fileTime;	// 50
		REX::W32::FILETIME saveTime;	// 58
		std::int32_t deviceID;			// 60
		bool loaded;					// 64
		bool corrupt;					// 65
		bool needsSync;					// 66
	};
	static_assert(sizeof(BGSSaveLoadFileEntry) == 0x68);
}
