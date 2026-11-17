#pragma once

namespace RE
{
	class BGSSaveLoadFileEntry
	{
	public:
		void DeleteGame()
		{
			using FuncType = decltype(&BGSSaveLoadFileEntry::DeleteGame);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadFileEntry::DeleteGame);
			std::invoke(FUNC, this);
		}

		void LoadData()
		{
			using FuncType = decltype(&BGSSaveLoadFileEntry::LoadData);
			static const auto FUNC = REL::Relocation<FuncType>(ID::BGSSaveLoadFileEntry::LoadData);
			std::invoke(FUNC, this);
		}

		// members
		char* fileName;					// 0x00
		char* playerName;				// 0x08
		char* playerTitle;				// 0x10
		char* location;					// 0x18
		char* playTime;					// 0x20
		char* raceName;					// 0x28
		std::int32_t version;			// 0x30
		std::uint32_t saveGameNumber;	// 0x34
		std::int32_t playerLevel;		// 0x38
		REX::Float32 levelProgress;		// 0x3C
		REX::Float32 levelThreshold;	// 0x40
		std::int32_t screenshotWidth;	// 0x44
		std::int32_t screenshotHeight;	// 0x48
		std::int32_t screenshotOffsetX; // 0x4C
		REX::W32::FILETIME fileTime;	// 0x50
		REX::W32::FILETIME saveTime;	// 0x58
		std::int32_t deviceID;			// 0x60
		bool loaded;					// 0x64
		bool corrupt;					// 0x65
		bool needsSync;					// 0x66
	};

	static_assert(sizeof(BGSSaveLoadFileEntry) == 0x68);
}
