#pragma once

#include "RE/B/BSFile.hpp"
#include "RE/B/BSSaveDataSystemUtility.hpp"
#include "RE/B/BSSaveDataSystemUtilityImage.hpp"

namespace RE
{
	class BSSaveDataSystemUtilityFile : public BSFile // 0x000
	{
	public:
		// members
		REX::StaticString<REX::W32::MAX_DIR> directoryName;						// 0x1B0
		bool singleSave;														// 0x2B0
		REX::StaticString<0x80> subtitle;										// 0x2B1
		REX::StaticString<0x400> detail;										// 0x331
		REX::StaticString<REX::W32::MAX_FNAME> createIconImagePath;				// 0x731
		BSSaveDataSystemUtilityImage createIconImage;							// 0x838
		BSSaveDataSystemUtilityImage iconImage;									// 0x850
		REX::StaticString<REX::W32::MAX_FNAME> iconImagePath;					// 0x868
		REX::StaticString<REX::W32::MAX_FNAME> backgroundImagePath;				// 0x968
		BSSaveDataSystemUtilityImage backgroundImage;							// 0xA68
		bool currentUserOwnsData;												// 0xA80
		bool updateMostRecentEntry;												// 0xA81
		BSSaveDataSystemUtility::SaveCompleteCallbackType saveCompleteCallback; // 0xA88
		BSSaveDataSystemUtility::LoadCompleteCallbackType loadCompleteCallback; // 0xA90
	};

	static_assert(sizeof(BSSaveDataSystemUtilityFile) == 0xA98);
}
