#pragma once

#include "RE/B/BSTSingleton.hpp"
#include "RE/P/PipboyInventoryData.hpp"
#include "RE/P/PipboyLogData.hpp"
#include "RE/P/PipboyMapData.hpp"
#include "RE/P/PipboyObject.hpp"
#include "RE/P/PipboyPerksData.hpp"
#include "RE/P/PipboyPlayerInfoData.hpp"
#include "RE/P/PipboyQuestData.hpp"
#include "RE/P/PipboyRadioData.hpp"
#include "RE/P/PipboySpecialData.hpp"
#include "RE/P/PipboyStatsData.hpp"
#include "RE/P/PipboyStatusData.hpp"
#include "RE/P/PipboyThrottleManager.hpp"
#include "RE/P/PipboyWorkshopData.hpp"

namespace RE
{
	class PipboyDataGroup;

	class _declspec(novtable) PipboyDataManager
		: public BSTSingletonSDM<PipboyDataManager> // 00
	{
	public:
		[[nodiscard]] static PipboyDataManager* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<PipboyDataManager**>{ ID::PipboyDataManager::Singleton };
			return *SINGLETON;
		}

		// members
		PipboyObject rootObject;					 // 008
		PipboyStatsData statsData;					 // 0A0
		PipboySpecialData specialData;				 // 1D8
		PipboyPerksData perksData;					 // 280
		PipboyInventoryData inventoryData;			 // 358
		PipboyQuestData questData;					 // 4F0
		PipboyWorkshopData workshopData;			 // 5D8
		PipboyLogData logData;						 // 718
		PipboyMapData mapData;						 // 7F0
		PipboyRadioData radioData;					 // A28
		PipboyPlayerInfoData playerInfoData;		 // AD8
		PipboyStatusData statusData;				 // BE0
		std::array<PipboyDataGroup*, 11> dataGroups; // CC0
		PipboyThrottleManager throttleManager;		 // D18
	};
	static_assert(sizeof(PipboyDataManager) == 0xD48);
}
