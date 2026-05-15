#pragma once

#include "RE/B/BSFile.hpp"
#include "RE/B/BSSaveDataSystemUtility.hpp"
#include "RE/B/BSSaveDataSystemUtilityImage.hpp"

namespace RE
{
	class BSSaveDataSystemUtilityFile
		: public BSFile // 000
	{
	public:
		// members
		std::array<char, REX::W32::MAX_DIR> directoryName;						// 1B0
		bool singleSave;														// 2B0
		std::array<char, 0x80> subtitle;										// 2B1
		std::array<char, 0x400> detail;											// 331
		std::array<char, REX::W32::MAX_FNAME> createIconImagePath;				// 731
		BSSaveDataSystemUtilityImage createIconImage;							// 838
		BSSaveDataSystemUtilityImage iconImage;									// 850
		std::array<char, REX::W32::MAX_FNAME> iconImagePath;					// 868
		std::array<char, REX::W32::MAX_FNAME> backgroundImagePath;				// 968
		BSSaveDataSystemUtilityImage backgroundImage;							// A68
		bool currentUserOwnsData;												// A80
		bool updateMostRecentEntry;												// A81
		BSSaveDataSystemUtility::SaveCompleteCallbackType saveCompleteCallback; // A88
		BSSaveDataSystemUtility::LoadCompleteCallbackType loadCompleteCallback; // A90
	};
	static_assert(sizeof(BSSaveDataSystemUtilityFile) == 0xA98);
}
