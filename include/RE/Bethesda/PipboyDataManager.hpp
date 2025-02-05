#pragma once

#include "RE/Bethesda/BSTSingleton.hpp"

#include "RE/Bethesda/PipboyDataGroup.hpp"
#include "RE/Bethesda/PipboyInventoryData.hpp"
#include "RE/Bethesda/PipboyLogData.hpp"
#include "RE/Bethesda/PipboyMapData.hpp"
#include "RE/Bethesda/PipboyPerksData.hpp"
#include "RE/Bethesda/PipboyPlayerInfoData.hpp"
#include "RE/Bethesda/PipboyQuestData.hpp"
#include "RE/Bethesda/PipboyRadioData.hpp"
#include "RE/Bethesda/PipboySpecialData.hpp"
#include "RE/Bethesda/PipboyStatsData.hpp"
#include "RE/Bethesda/PipboyStatusData.hpp"
#include "RE/Bethesda/PipboyThrottleManager.hpp"
#include "RE/Bethesda/PipboyValue.hpp"
#include "RE/Bethesda/PipboyWorkshopData.hpp"

namespace RE
{
	class _declspec(novtable) PipboyDataManager
		: public BSTSingletonSDM<PipboyDataManager> // 00
	{
	public:
		[[nodiscard]] static PipboyDataManager* GetSingleton()
		{
			static REL::Relocation<PipboyDataManager**> singleton{ REL::RelocationID(1178971, 2689086) };
			return *singleton;
		}

		// members
		PipboyObject rootObject;			   // 08
		PipboyStatsData statsData;			   // A0
		PipboySpecialData specialData;		   // 1D8
		PipboyPerksData perksData;			   // 280
		PipboyInventoryData inventoryData;	   // 358
		PipboyQuestData questData;			   // 4F0
		PipboyWorkshopData workshopData;	   // 5D8
		PipboyLogData logData;				   // 718
		PipboyMapData mapData;				   // 7F0
		PipboyRadioData radioData;			   // A28
		PipboyPlayerInfoData playerInfoData;   // AD8
		PipboyStatusData statusData;		   // BE0
		PipboyDataGroup* dataGroups[11];	   // CC0
		PipboyThrottleManager throttleManager; // D18
	};
	static_assert(sizeof(PipboyDataManager) == 0xD48);
}