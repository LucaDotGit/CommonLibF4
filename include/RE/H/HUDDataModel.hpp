#pragma once

#include "RE/B/BSInputEventReceiver.hpp"
#include "RE/B/BSSpinLock.hpp"
#include "RE/B/BSTEvent.hpp"
#include "RE/B/BSTSingleton.hpp"
#include "RE/C/CalculateCompassMarkersFunctor.hpp"
#include "RE/C/ConditionBoyEvent.hpp"
#include "RE/H/HUDActiveEffectsModel.hpp"
#include "RE/H/HUDAmmoCountModel.hpp"
#include "RE/H/HUDDirectionalHitIndicatorDataModel.hpp"
#include "RE/H/HUDExplosivesDataModel.hpp"
#include "RE/H/HUDMessagesModel.hpp"
#include "RE/H/HUDNotificationsModel.hpp"
#include "RE/H/HUDPerkVaultBoyModel.hpp"
#include "RE/H/HUDRadiationModel.hpp"
#include "RE/H/HUDRolloverModel.hpp"
#include "RE/H/HUDTargetHealthModel.hpp"

namespace RE
{
	class __declspec(novtable) HUDDataModel
		: public BSInputEventReceiver,		   // 0000
		  public BSTSingletonSDM<HUDDataModel> // 0010
	{
	public:
		inline static constexpr auto RTTI{ RTTI::HUDDataModel };
		inline static constexpr auto VTABLE{ VTABLE::HUDDataModel };

		// override (BSInputEventReceiver)
		void PerformInputProcessing(const InputEvent* a_queueHead) override; // 00

		// add
		virtual ~HUDDataModel(); // 01

		[[nodiscard]] static HUDDataModel* GetSingleton()
		{
			static const auto SINGLETON = REL::Relocation<HUDDataModel**>{ ID::HUDDataModel::Singleton };
			return *SINGLETON;
		}

		// members
		HUDRolloverModel rolloverModel;										  // 0018
		HUDTargetHealthModel targetHealthModel;								  // 05C0
		HUDRadiationModel radiationModel;									  // 0698
		HUDExplosivesDataModel explosivesDataModel;							  // 0910
		HUDDirectionalHitIndicatorDataModel directionalHitIndicatorDataModel; // 0968
		HUDAmmoCountModel ammoCountModel;									  // 09E0
		HUDMessagesModel messagesModel;										  // 0A08
		HUDPerkVaultBoyModel perkVaultBoyModel;								  // 0B68
		HUDNotificationsModel notificationsModel;							  // 0C40
		HUDActiveEffectsModel activeEffectsModel;							  // 0EC0
		BSTValueEventSource<ConditionBoyEvent> conditionBoy;				  // 1320
		CalculateCompassMarkersFunctor compassMarkerFunctor;				  // 1340
		mutable BSSpinLock compassMarkerArrayLock;							  // 1398
	};
	static_assert(sizeof(HUDDataModel) == 0x13A0);
}
